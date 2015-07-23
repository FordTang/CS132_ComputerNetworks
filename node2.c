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

int connectcosts2[4] = { 3, 1, 0, 2 };

struct distance_table
{
  int costs[4][4];
} dt2;


/* students to write the following two routines, and maybe some others */


void sendUpdate2()
{
  connectcosts2[0] = dt2.costs[2][0];
  connectcosts2[1] = dt2.costs[2][1];
  connectcosts2[2] = dt2.costs[2][2];
  connectcosts2[3] = dt2.costs[2][3];

  struct rtpkt to0, to1, to3;

  to0.sourceid = 2;
  to0.destid = 0;

  to1.sourceid = 2;
  to1.destid = 1;

  to3.sourceid = 2;
  to3.destid = 3;

  int i;

  for (i = 0; i < 4; ++i)
  {
  	to0.mincost[i] = connectcosts2[i];
  	to1.mincost[i] = connectcosts2[i];
  	to3.mincost[i] = connectcosts2[i];
  }

  tolayer2(to0);
  tolayer2(to1);
  tolayer2(to3);
}


void rtinit2()
{
  dt2.costs[2][0] = 3;
  dt2.costs[2][1] = 1;
  dt2.costs[2][2] = 0;
  dt2.costs[2][3] = 2;

  sendUpdate2();
}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  int i;
  unsigned char update = 0;

  for (i = 0; i < 4; ++i)
  {
    if ((rcvdpkt->mincost[i] + dt2.costs[2][rcvdpkt->sourceid]) < dt2.costs[0][i])
    {
      dt2.costs[2][i] = rcvdpkt->mincost[i] + dt2.costs[2][rcvdpkt->sourceid];
      update = 1;
    }
  }

  if (1 == update)
    sendUpdate2();
}


printdt2(dtptr)
  struct distance_table *dtptr;
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}