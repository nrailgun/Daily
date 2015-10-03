/*
 * Advanced Software Engineering HW.4 P3.
 */

chan request = [2] of { byte, chan };

active [2] proctype Server()
{
	byte client;
	chan reply_chan;

	do
	:: request ? client, reply_chan ->
		printf("Client %d processed by Server %d.\n", client, _pid);
		reply_chan ! _pid;
	od
}

active [5] proctype Client()
{
	chan cc = [2] of { byte };
	byte srvid;

	do
	:: request ! _pid, cc ->
		cc ? srvid;
		printf("Client %d is served by Server %d.\n", _pid, srvid);
	od
}
