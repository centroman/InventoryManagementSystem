#include <stdio.h>
#include <stdlib.h>

FILE *item_stock; //Pointer to file

/* Basic structure of the inventory features */
struct item_Info
{
    char name[20];
    float cost;
    int stock;
    float profit;
    int sold;
}iteminfo[10];

/* Function -1 To enter the inventory product info when the program is started by using case d*/
void enterdata(int n,int k)
{   int i=k;
    while(i<n)
    {
    printf("\nEnter the item name : ");
    scanf("%s",&iteminfo[i].name);
    fflush(stdin);
    printf("\nEnter the cost of item : ");
    scanf("%f",&iteminfo[i].cost);
    fflush(stdin);
    printf("\nEnter the no. of items in stock : ");
    scanf("%d",&iteminfo[i].stock);
    fflush(stdin);
    iteminfo[i].profit=0;
     i++;
    }

}
/* Function 2- To display the data of the inventory  case a*/
void display()
{
    int n = file_read();
    if(n!=0)
    {
    int i=0;
    printf("\nItemNumber\tItemName\tStock\t\tUnitCost\tValue");
    while(i<n)
    {
      printf("\n   %d",i+1);
      printf("\t\t%s",iteminfo[i].name);
      printf("\t\t%d",iteminfo[i].stock);
      printf("\t\t%.3f",iteminfo[i].cost);
      float value=iteminfo[i].cost *iteminfo[i].stock;
      printf("\t\t%.3f",value);
      i++;
    }
    }
    else
    {
        printf("\nInventory is empty");
    }

}
/* Function 3- To read the file*/
int file_read()
{   item_stock=fopen("stock.dat","rb");
    int i=0;
    while(fread(&iteminfo[i], sizeof(struct item_Info), 1, item_stock))
    {
      i++;
    }
    fclose(item_stock);

    return i;

}

//Function -4 To write the data of the inventory in the file

void file_write(int n)
{
    item_stock=fopen("stock.dat","wb");
    int i=0;
    while(i<n)
    {
      fwrite(&iteminfo[i], sizeof(struct item_Info), 1, item_stock);
      i++;
    }
    fclose(item_stock);
}

// Function -5 Part of the case d
void enter_datas()
{
  int n;
  printf("How many new items to be added\n");
  scanf("%d",&n);
  fflush(stdin);
  int k=file_read();
  int k1=k+n;
  if(k1<=10)
  {
      enterdata(k1,k);
      file_write(k1);
  }
  else
    {
    printf("\n Inventory is full");
  }

}
// Function -6 Part of case e , Allows the owner to add the sale information to the inventory
void enter_sale_data()
{
   int n= file_read();
    int i=0;
    while(i<n)
    {
      printf("\n\tItem Name : %s",iteminfo[i].name);
      printf("\nEnter the items sold : ");
      scanf("%d",&iteminfo[i].sold);
      fflush(stdin);
      iteminfo[i].stock=iteminfo[i].stock-iteminfo[i].sold;
      iteminfo[i].profit=((iteminfo[i].cost)/2)*(iteminfo[i].sold) + iteminfo[i].profit;
      i++;
    }
    file_write(n);
}

// Function- 7 Part of case- b to display the info of the sale profit
void display_sale_data()
{
    int n=file_read();
    if(n!=0)
    {
    int i=0;
    float total_profit;

    printf("\nItem_Number\tItem_Name\t\tNumber_Sold\tItem_Profit");
    while(i<n)
    {
      printf("\n   %d",i+1);
      printf("\t\t%s",iteminfo[i].name);
      printf("\t\t\t%d",iteminfo[i].sold);
      printf("\t\t%.3f",iteminfo[i].profit);
      total_profit= total_profit+iteminfo[i].profit;
      i++;
    }
    printf("\n\nTotal Profit: %0.3f",total_profit);
   }
   else
   {
       printf("No sale data");
   }
}
// Function- 8 To modify the stock
void add_existing_items()
{
    int n=file_read();
    int i=0,num;
    while(i<n)
    {
      printf("\n\tItem Name: %s",iteminfo[i].name);
      printf("\nEnter the number of items:");
      scanf("%d",&num);
      fflush(stdin);
      iteminfo[i].stock=iteminfo[i].stock+num;
      i++;
    }
    file_write(n);
}

int main()
{
    char response;

  do {
    printf("\n\nMAIN MENU\n");
    printf("Press a to show the details of the items in stock\n");
    printf("Press b to show the details of the items after sale\n");
    printf("Press c to order more of existing items\n");
    printf("Press d to order new items\n");
    printf("Press e to enter the details of the sale\n");
    printf("Press f to quit\n\n");
    scanf("%c",&response);
    fflush(stdin);
    switch(response)
    {
    case 'a' : display();
               break;
    case 'b' : display_sale_data();
               break;
    case 'c' : add_existing_items();
                  break;
    case 'd' : enter_datas();
                 break;
    case 'e' : enter_sale_data();
                break;
    case 'f' :  exit(0);
    }
} while(1);

    return 0;
}
