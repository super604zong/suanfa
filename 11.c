# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX 30
# define INEF 99999
typedef struct
{
	int num;
	char name[MAX];
}City;


typedef struct
{
	char trans[30];
	int money;
	int time;
	int mile;
}Node;
typedef struct{
	Node arc[MAX][MAX];//用于存放各个城市之间的边 的信息 
    City vex[MAX];//用于存放各个城市的信息 
    int arcnum;
    int vexnum;
}Adj;


int dist[MAX];
int path[MAX][MAX];
int xiabiao(Adj *G, char name[])
{
	int i;
	for(i = 1; i<=G->vexnum; i++)
	{
          printf("%s   %s\n",name, G->vex[i].name);
		if(strcmp(name,G->vex[i].name)==0)
		 return i;
	}
	printf("没有找到\n");
	exit(-1);
}


void Dijkstra(Adj *G, int start, int end, int dist[], int path[][MAX])
{
	int min, i,j,k,t=1;
	
	//初始化dist数组用来存 出发点到其他各城市的最小距离值 
	for(i = 1; i<=G->vexnum; i++)
	{
		dist[i] = G->arc[start][i].time;//先记录下从原点到其他各点的值， 下标代表其他城市对应的下标 
		if(G->arc[start][i].time != INEF)
		{
			path[i][1] = start;//将起点到其他各点的值不为空， 就将起点的下标 放入path[i][1]中 
		}
	}
	path[start][0] = 1;//将起点标记
	
	//寻找从起点到其他个点的最下的值 
	for(i = 2 ; i<=G->vexnum; i++)
	{
		min = INEF;
		
		//寻找从起点到其他个点的最下的值 
		for(j = 1; j<=G->vexnum; j++)
		{
			if(!path[j][0] && dist[j]< min)//从未标记的城市，并且该城市与起点城市的值要最小，找到该城市的下标，和最小值 
			{
				k = j;
				min = dist[j];
			}
		}
		
		
		
		//这块只是用来 找从刚才最小值点到其他 （起点与其它有关联的点） 之间距离和 小于 起点到其他有关联的点的值，就修改dist  
		if(min == INEF)  return;
		path[k][0] = 1;//将刚才找到的最小值的城市进行标记
		for(j = 1; j<=G->vexnum; j++)
		{
			if(!path[j][0] && G->arc[k][j].time < INEF && dist[k] +G->arc[k][j].time < dist[j])//因为dist[]中存储的是从起点到其他各城市的最小值，这个数组会不断修改 
			{
                          dist[j] = dist[k] + G->arc[k][j].time;//相当于开始是A->B是最小的,然后由B开始找与它相关联 C 的最小的值，如果小于dist[j]（A->C->B）， 就修改 
                          t=1;
                          while(path[k][t] !=0)
                         {
                	   path[j][t] = path[k][t];//
                	   t++;//跳出循环 
	         	}
		        path[j][t] = k;//让下一次找最短路径从先前已找到最下值的点开始继续找 
		        path[j][t+1] = 0;
				 				
	                 }
		 }
		
		
		 
	 } 
	 
	// for(i= 1; i<=G->vexnum; i++) 
     	// {  if(i==end)  break;
            i =end;
 	    printf("%s到%s的最快的路线:\n 从%s", G->vex[start].name, G->vex[end].name, G->vex[start].name);
            for(j =2; path[i][j] != 0 ; j++)
	    {
               // printf("%dn",path[i][j]); 
		printf("-->%s", G->vex[path[i][j]].name);
	     //	if(G->vex[path[i][j]].name == name2)
	     //	break; 
	    } 
            printf("-->%s\n",G->vex[end].name);
	    printf("所用时间为:%d\n",dist[i]);
//	}
	
}

void quick(Adj *G)
{
	int i, j,start , end;
	char name1[30], name2[30]; 
	printf("请输入起点：");
	scanf("%s",name1);
	printf("请输入终点: ");
	scanf("%s",name2);
	start = xiabiao(G, name1);
	end = xiabiao(G, name2);
        printf("strat:%d end:%d\n",start, end);
	Dijkstra(G, start, end, dist, path);
	/*
//	printf("最快的路线: \n");
	for(i= 1; i<=G->vexnum; i++)
		if(i==start)  break;
	
	printf("%s到%s的最快的路线: 从%s-->\n", name1, name2, name1);
	for(j =2; path[i+1][j] !=0 ; j++)
	{
		printf("-->%s", G->vex[path[i+1][j]].name);
		if(G->vex[path[i+1][j]].name == name2)
		   break; 
	} 
	printf("距离为:%d\n",dist[j]);
     
	*/
	
	
}

void showAdj(Adj *G)
{
	int i,j;
	for(i= 1; i<=G->vexnum; i++)
	{
		for(j = 1; j<=G->vexnum; j++)
		{
			if(G->arc[i][j].trans != "NULL")
			printf("%s<--->%s\n",G->vex[i].name,G->vex[j].name);
	        printf("出行方式: %s\n", G->arc[i][j].trans);
			printf("所需时间：%d\n", G->arc[i][j].time);
			printf("金钱: %d\n", G->arc[i][j].money);
			printf("公里数: %d\n",G->arc[i][j].mile); 
			
		}
	}
}



//用邻接矩阵存储各个城市以及道路信息

void create(Adj *G)
{
	int i,j,a,b,time,money,mile;
	char enter,name1[30], name2[30], trans[30];
	printf("请输入城市的个数和交通路线数:\n");
	scanf("%d%d",&G->vexnum, &G->arcnum);
	for(i = 1; i<=G->vexnum; i++)
	{
		for(j = 1; j<=G->vexnum; j++)
		{
		//	G.arc[i][j].trans="NULL";
		    strcpy(G->arc[i][j].trans, "NULL");
			G->arc[i][j].mile=INEF;
			G->arc[i][j].money =INEF;
			G->arc[i][j].time=INEF;
		}
	 } 
	 printf("请输入各个城市的名字:\n");
	 for(i = 1; i<=G->vexnum; i++)
	 {
	 	G->vex->num = i;
	 	scanf("%s",G->vex[i].name);
	 }
      printf("请输入各个城市之间路线的信息(起点城市，终点城市，交通工具,需要的时间， 路程，钱):\n");
      for(i = 1; i<=G->arcnum; i++)
      {
      	  scanf("%s",name1);
      	  a = xiabiao(G, name1);
      	  scanf("%s",name2);
      	  b = xiabiao(G, name2);
      	  
      	  scanf("%s",trans);
      	  scanf("%d%d%d",&time,&mile, &money);
      	
		  
		  strcpy(G->arc[a][b].trans,trans);
      	  G->arc[a][b].time =  time;
		  G->arc[a][b].mile = mile;
		  G->arc[a][b].money = money;
		  
		  strcpy(G->arc[b][a].trans, trans);
		  G->arc[b][a].time = time;
		  G->arc[b][a].mile = mile;
		  G->arc[b][a].money = money;
	  }
}

int main(void)
{
	Adj G;
//	create(&G);
	int choice;
	do{
		printf("1:重新创建一个全国交通网络图\n");
		printf("2:显示当前的交通网络\n");
		printf("3:添加一个条新的路线\n");
		printf("4:删除一条路线\n");
		printf("5:按照最快的方式到达\n");
		printf("6:按照最省钱的方式到达\n");
		printf("7:按照中转的次数最少到达\n");
		printf("请输入你的选择(1-7): ");
		scanf("%d",&choice); 
		
		switch(choice)
		{
                   case 1:create(&G);
		   break;
		   case 2:showAdj(&G);
		   break;
		   case 3://add(G);
		   break;
		   case 4://delate(G);
		   break;
		   case 5:quick(&G);
		   break;
		   case 6://savemoney(G);
		   break;
		   case 7://numben(G);	
		   		break;
	
		}
	}while(1);
	
	return 0;
}




