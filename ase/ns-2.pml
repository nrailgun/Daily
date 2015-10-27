// Author: NR

mtype = {
	OK, ERR, MSG_1, MSG_2, MSG_3,
	KEY_A, KEY_B, AGENT_A, AGENT_B, NOUNCE_A, NOUNCE_B
};

typedef Crypt {
	mtype k, c1, c2;
};

chan inet = [0] of { mtype /*msg_id*/, mtype /*receiver*/, Crypt };

mtype partner_a = AGENT_B, partner_b = AGENT_A;
mtype status_a = ERR, status_b = ERR;

active proctype Alice() {
	/* local variables */
	mtype pubkey;     /* the other agent's public key                 */
	mtype pnonce;     /* nonce that we receive from the other agent   */
	Crypt msgab;      /* our encrypted message to the other party     */
	Crypt received;   /* received encrypted message                   */

	/* Initialization  */
	partner_a = AGENT_B;
	pubkey = KEY_B; 

	/* Prepare the first message */
	msgab.k = pubkey;
	msgab.c1 = AGENT_A;
	msgab.c2 = NOUNCE_A;

	/* Send the first message to the other party */
	inet ! MSG_1 (partner_a, msgab);

	/* Wait for an answer. Observe the we are pattern-matching on the
	   messages that start with MSG_2 and AGENT_A, that is, we block until 
	   we see a message with values MSG_2 and AGENT_A as the first and second  
	   components. The third component is copied to the variable received. */
	inet ? (MSG_2, AGENT_A, received);

	/* We proceed only if the key field of the received matches KEY_A and the
	   received nonce is the one that we have sent earlier; block
	   otherwise.  */
	(received.k == KEY_A) && (received.c1 == NOUNCE_A);

	/* Obtain Bob's nonce */
	pnonce = received.c2;

	/* Prepare the last message */  
	msgab.k = pubkey;
	msgab.c1 = pnonce; 
	/* c2 is not used in the last message, just set it to 0 */
	msgab.c2 = 0; 

	/* Send the prepared messaage */
	inet ! MSG_3 (partner_a, msgab);

	/* and last - update the auxilary status variable */
	printf("Alice\n");
	status_a = OK;
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

	inet ? MSG_1, AGENT_B, received;
	received.k == KEY_B;

	pubkey = KEY_A; // How do I get what is the key for the sender?
	sender = received.c1;
	nonce = received.c2;

	msgba.k = pubkey;
	msgba.c1 = nonce;
	msgba.c2 = NOUNCE_B;
	inet ! MSG_2, sender, msgba;

	inet ? MSG_3, AGENT_B, received;
	(received.k == KEY_B) && (received.c1 == NOUNCE_B);

	printf("Bob\n");
	status_b = OK;
}

ltl {
	<> (status_a == OK && status_b == OK)
}
