#include <stdio.h>
#include <stdlib.h>
#include "cgraph/cgraph.h"

void task1()
{
	FILE *input=fopen("../tiepxucgan.txt","r");
	if(input == NULL) 
	{
	  printf("Xay ra loi khi mo tiepxucgan.txt !!!");
	  return 0;
	}
	int n;
	fscanf(input,"%d\n",&n);
	for(int i=0;i<n;i++)
	{
		char nguoi1;
		fscanf(input,"%c ",&nguoi1);
		printf("%c ",nguoi1);
		// int dem=0;
		char nguoi2;
		while(1)
		{
			nguoi2=fgetc(input);
			if(nguoi2=='\n'||nguoi2==EOF) break;
			while(nguoi2==' ') nguoi2=fgetc(input);
			printf("%c ",nguoi2);
		}
		printf("\n");
	}
}
int main()
{
//Doc file tiepxucgan.txt
	FILE *input=fopen("../tiepxucgan.txt","r");
	FILE *output=fopen("../newtxgan.txt","w");
	if(input == NULL) 
	{
	  printf("Xay ra loi khi mo tiepxucgan.txt !!!");
	  return 0;
	}
	int n;
	fscanf(input,"%d\n",&n);
	cgraph_ivec_t edges = cgraph_ivec_create();
	for(int i=0;i<n;i++)
	{
		char nguoi1;
		fscanf(input,"%c ",&nguoi1);
		// int dem=0;
		char nguoi2;
		while(1)
		{
			nguoi2=fgetc(input);
			if(nguoi2=='\n'||nguoi2==EOF) break;
			while(nguoi2==' ') nguoi2=fgetc(input);
			cgraph_ivec_push_back(&edges, nguoi1);
			cgraph_ivec_push_back(&edges, nguoi2);
			// printf("%d %d\n",nguoi1,nguoi2);
		}
	}
	cgraph_t g = cgraph_create(edges, 0, CGRAPH_UNDIRECTED);
	int lenh=0;
//menu
	do
	{
		printf("==Menu chuong trinh\n");
		printf("1. Doc file va In toan bo danh sach tiep xuc gan\n2. Kiem tra tiep xuc\n3. Tiep xuc gan cua 1 nguoi\n4. Tiep xuc gan voi nhieu nguoi nhat\n5. Nhap F0, in ra F1 F2\n6. Them tiep xuc gan (X)\n7. Them tiep xuc gan (Nguoi da co trong danh sach)\n8. Ghi danh sach tiep xuc gan ra file text\n9. Thoat\n");
		scanf("%d",&lenh);
		if(lenh<1||lenh>9) printf("LENH SAI! NHAP LAI!\n");
		else if(lenh==1)
		{
//task1
			task1();
		}
		else if(lenh==2)
		{
//task2
			char test1,test2;
			printf("Nhap 2 nguoi: ");getc(stdin);scanf("%c %c",&test1,&test2);
			int eid;
			cgraph_get_eid(g, &eid,
                   test1, test2,
                   CGRAPH_UNDIRECTED);
			// printf("%d %d %d\n",test1,test2,eid);
			if(eid<0) printf("Khong tiep xuc\n");
			else printf("Co tiep xuc\n");
		}
		else if(lenh==3)
		{
//task 3
			char test;
			printf("Nhap ten nguoi: ");getc(stdin);scanf("%c",&test);
			cgraph_ivec_t neis = cgraph_ivec_create();
			cgraph_neighbors(g,&neis,test,CGRAPH_ALL);
			for(int i=0; i<cgraph_ivec_size(neis);i+=2)
			{
				printf("%c ",neis[i]);
			}
			printf("\n");
		}
		else if(lenh==4)
		{
//task4
			cgraph_ivec_t res = cgraph_ivec_create();
			cgraph_degree_all(g,&res,CGRAPH_ALL,0);
			int max=0;char id;
			for(int i=0; i<cgraph_ivec_size(res);i++)
			{
				if(res[i]>max) 
				{
					id=i;
					max=res[i];
				}
			}
			printf("Tiep xuc nhieu nhat:%c %d\n",id,max/2);
		}
		else if(lenh==5)
		{
//task5
			char f0;
			printf("Nhap F0: ");getc(stdin);scanf("%c",&f0);
			cgraph_ivec_t neis1 = cgraph_ivec_create();
			cgraph_neighbors(g,&neis1,f0,CGRAPH_ALL);
			cgraph_ivec_t f0f1 = cgraph_ivec_create();
			cgraph_ivec_push_back(&f0f1, f0);
			printf("Danh sach F1: ");
			for(int i=0; i<cgraph_ivec_size(neis1);i+=2)
			{
				printf("%c ",neis1[i]);
				cgraph_ivec_push_back(&f0f1, neis1[i]);
			}
			printf("\n");
			printf("Danh sach F2: ");
			for(int i=0; i<cgraph_ivec_size(neis1);i+=2)
			{
				cgraph_ivec_t neis2 = cgraph_ivec_create();
				cgraph_neighbors(g,&neis2,neis1[i],CGRAPH_ALL);
				for(int i=0; i<cgraph_ivec_size(neis2);i+=2)
				{
					int check=0;
					for(int j=0; j<cgraph_ivec_size(f0f1);j++)
					{
						if(neis2[i]==f0f1[j]) check=1;
					}
					if(check==0) printf("%c ",neis2[i]);
				}
			}
			printf("\n");
		}
		else if(lenh==6)
		{
//task6
			char new;
			printf("Nhap nguoi them vao danh sach tiep xuc: ");getc(stdin);scanf("%c",&new);
			cgraph_add_vertices(g, new);
			cgraph_ivec_t newedges = cgraph_ivec_create();
			do
			{
				char tiepxuc;
				printf("Nhap tiep xuc (Nhap 0 de ket thuc): ");getc(stdin);scanf("%c",&tiepxuc);
				if(tiepxuc=='0') break;
				cgraph_ivec_push_back(&newedges, new);
				cgraph_ivec_push_back(&newedges, tiepxuc);
				cgraph_ivec_push_back(&newedges, tiepxuc);
				cgraph_ivec_push_back(&newedges, new);
			}while(1);
			cgraph_add_edges(g, newedges);
		}
		else if(lenh==7)
		{
//task7
			char tx1,tx2;
			printf("Nhap 2 nguoi: ");getc(stdin);scanf("%c %c",&tx1,&tx2);
			cgraph_ivec_t newedges = cgraph_ivec_create();
			cgraph_ivec_push_back(&newedges, tx1);
			cgraph_ivec_push_back(&newedges, tx2);
			cgraph_ivec_push_back(&newedges, tx2);
			cgraph_ivec_push_back(&newedges, tx1);
			cgraph_add_edges(g, newedges);
		}
		else if(lenh==8)
		{
//task8
			// printf("%d \n",cgraph_vcount(g));
			cgraph_ivec_t res = cgraph_ivec_create();
			cgraph_degree_all(g,&res,CGRAPH_ALL,0);
			for(int i=0; i<cgraph_ivec_size(res);i++)
			{
				if(res[i]>0) fprintf(output,"%c ",i);
				cgraph_ivec_t neis = cgraph_ivec_create();
				cgraph_neighbors(g,&neis,i,CGRAPH_ALL);
				for(int j=0; j<cgraph_ivec_size(neis);j+=2)
				{
					fprintf(output,"%c ",neis[j]);
				}
				if(res[i]>0) fprintf(output,"\n");
			}
			// for(int i=0;i<n;i++)
			// {
			// 	int id=i+65;
			// 	printf("%c ",id);
			// 	cgraph_ivec_t neis = cgraph_ivec_create();
			// 	cgraph_neighbors(g,&neis,id,CGRAPH_ALL);
			// 	for(int j=0; j<cgraph_ivec_size(neis);j+=2)
			// 	{
			// 		printf("%c ",neis[j]);
			// 	}
			// 	printf("\n");
			// }

		}
	}while(lenh!=9);
	cgraph_destroy(&g);
	fclose(input);fclose(output);
	return 0;
}