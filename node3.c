#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

int connectcosts3[4] = { 7, 999, 2, 0 };

struct distance_table
{
  int costs[4][4];
} dt3;


/* students to write the following two routines, and maybe some others */


void sendUpdate3()
{
  connectcosts3[0] = dt3.costs[3][0];
  connectcosts3[1] = dt3.costs[3][1];
  connectcosts3[2] = dt3.costs[3][2];
  connectcosts3[3] = dt3.costs[3][3];

  struct rtpkt to0, to2;

  to0.sourceid = 3;
  to0.destid = 0;

  to2.sourceid = 3;
  to2.destid = 2;

  int i;

  for (i = 0; i < 4; ++i)
  {
	to0.mincost[i] = connectcosts3[i];
  	to2.mincost[i] = connectcosts3[i];
  }

  tolayer2(to0);
  tolayer2(to2);
}


void rtinit3()
{
  dt3.costs[3][0] = 7;
  dt3.costs[3][1] = 999;
  dt3.costs[3][2] = 2;
  dt3.costs[3][3] = 0;

  sendUpdate3();
}


void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int i;
  unsigned char update = 0;

  for (i = 0; i < 4; ++i)
  {
    if ((rcvdpkt->mincost[i] + dt3.costs[3][rcvdpkt->sourceid]) < dt3.costs[3][i])
    {
      dt3.costs[3][i] = rcvdpkt->mincost[i] + dt3.costs[3][rcvdpkt->sourceid];
      update = 1;
    }
  }

  if (1 == update)
    sendUpdate3();
}


printdt3(dtptr)
  struct distance_table *dtptr;

{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
}