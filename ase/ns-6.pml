// Author: NR

mtype = { ok, err, msg1, msg2, msg3, keyA, keyB, agentA, agentB,
	nonceA, nonceB, agentI, keyI, nonceI };

typedef Crypt { mtype key, content1, content2 };

chan network = [0] of { mtype, /* msg# */
                        mtype, /* receiver */
                        Crypt
};

/* global variables for verification*/
mtype partnerA, partnerB;
mtype statusA = err;
mtype statusB = err; 
bool knows_nonceA = false, knows_nonceB = false;

ltl ltl1 {
	[] (statusA == ok && statusB == ok -> partnerA == agentB && partnerB == agentA)
}

ltl ltl2 {
	[] (statusA == ok && partnerA == agentB -> !knows_nonceA)
}

ltl ltl3 {
	[] (statusB == ok && partnerB == agentA -> !knows_nonceB)
}

/* Agent (A)lice */
active proctype Alice() {
  /* local variables */
  
  mtype pkey;      /* the other agent's public key                 */
  mtype pnonce;    /* nonce that we receive from the other agent   */
  Crypt messageAB; /* our encrypted message to the other party     */
  Crypt data;      /* received encrypted message                   */


  /* Initialization  */
  
  if
    :: partnerA = agentB;
       pkey     = keyB; 
    :: partnerA = agentI;
       pkey     = keyI;
  fi

  /* Prepare the first message */
  
  messageAB.key = pkey;
  messageAB.content1 = agentA;
  messageAB.content2 = nonceA;  

  /* Send the first message to the other party */
  
  network ! msg1 (partnerA, messageAB);

  /* Wait for an answer. Observe the we are pattern-matching on the
     messages that start with msg2 and agentA, that is, we block until 
     we see a message with values msg2 and agentA as the first and second  
     components. The third component is copied to the variable data. */

  network ? (msg2, agentA, data);

  /* We proceed only if the key field of the data matches keyA and the
     received nonce is the one that we have sent earlier; block
     otherwise.  */

  (data.key == keyA) && (data.content1 == nonceA);

  /* Obtain Bob's nonce */
  
  pnonce = data.content2;

  /* Prepare the last message */  
  messageAB.key = pkey;
  messageAB.content1 = pnonce; 
  messageAB.content2 = 0;  /* content2 is not used in the last message,
                              just set it to 0 */

  
  /* Send the prepared messaage */
  network ! msg3 (partnerA, messageAB);

  
  /* and last - update the auxilary status variable */
  statusA = ok;
}

/*
 * X -> Y: {X, NX}_{kY}
 * Y -> X: {NX, NY}_{kX}
 * X -> Y: {NY}_{kY}
 */
active proctype Bob()
{
	mtype pubkey;
	mtype sender;
	mtype nonce;
	Crypt msgba;
	Crypt received;

	network ? msg1, agentB, received;
	(received.key == keyB) && (received.content1 == agentA);

	sender = received.content1;
	partnerB = agentA;
	pubkey = keyA;
	nonce = received.content2;

	msgba.key = pubkey;
	msgba.content1 = nonce;
	msgba.content2 = nonceB;
	network ! msg2, sender, msgba;

	network ? msg3, agentB, received;
	(received.key == keyB) && (received.content1 == nonceB);

	printf("Bob is OK.\n");
	statusB = ok;
}

/*
 * X -> Y: {X, NX}_{kY}
 * Y -> X: {NX, NY}_{kX}
 * X -> Y: {NY}_{kY}
 */
active proctype Intruder() {
	mtype msg, partner, recpt;
	Crypt data, intercepted;
	do
	:: network ? (msg, partner, data) ->
		if
		:: data.key == keyI && msg == msg1 -> // send by A
			knows_nonceA = true;
		:: data.key == keyI && msg == msg2 -> // send by B
			knows_nonceA = true;
			knows_nonceB = true;
		:: data.key == keyI && msg == msg3 -> // send by A
			knows_nonceB = true;
		:: else ->
			skip;
		fi

		if /* perhaps store the message */
		:: intercepted.key   = data.key;
		   intercepted.content1 = data.content1;
		   intercepted.content2 = data.content2;
		:: skip;
		fi ;
	
	:: /* Replay or send a message */
		if /* choose message type */
			:: msg = msg1;
			:: msg = msg2;
			:: msg = msg3;
		fi ;
		if /* choose a recepient */
			:: recpt = agentA;
			:: recpt = agentB;
		fi ;
		if /* replay intercepted message or assemble it */
		::
			data.key       = intercepted.key;
			data.content1  = intercepted.content1;
			data.content2  = intercepted.content2;
		::
			if /* assemble key */
			:: recpt == agentA ->
				data.key = keyA;
			:: recpt == agentB ->
				data.key = keyB;
			fi ;
			if /* assemble content1 */
			:: msg == msg1 ->
			      	data.content1 = agentA;
			:: msg == msg1 ->
		      		data.content1 = agentB;
			:: msg == msg1 ->
		      		data.content1 = agentI;

			:: msg == msg2 ->
				data.content1 = nonceI;
			:: msg == msg2 && knows_nonceA ->
				data.content1 = nonceA;
			:: msg == msg2 && knows_nonceB ->
				data.content1 = nonceB;
			:: msg == msg2 ->
				data.content1 = intercepted.content1;
			:: msg == msg2 ->
				data.content1 = intercepted.content2;

			:: msg == msg3 ->
				data.content1 = nonceI;
			:: msg == msg3 && knows_nonceA ->
				data.content1 = nonceA;
			:: msg == msg3 && knows_nonceB ->
				data.content1 = nonceB;
			:: msg == msg3 ->
				data.content1 = intercepted.content1;
			:: msg == msg3 ->
				data.content1 = intercepted.content2;

			:: else ->
				assert(false);
			fi ;

			if // Assemble content 2
			:: msg == msg1 ->
				data.content2 = nonceI;
			:: msg == msg1 && knows_nonceA ->
				data.content2 = nonceA;
			:: msg == msg1 && knows_nonceB->
				data.content2 = nonceB;
			:: msg == msg1 ->
				data.content2 = intercepted.content1;
			:: msg == msg1 ->
				data.content2 = intercepted.content2;

			:: msg == msg2 ->
				data.content2 = nonceI;
			:: msg == msg2 && knows_nonceA ->
				data.content2 = nonceA;
			:: msg == msg2 && knows_nonceB->
				data.content2 = nonceB;
			:: msg == msg2 ->
				data.content2 = intercepted.content1;
			:: msg == msg2 ->
				data.content2 = intercepted.content2;

			:: msg == msg3 ->
				data.content2 = 0;

			:: else ->
				assert(false);
			fi
		fi ;
		network ! msg (recpt, data);
	od
}
