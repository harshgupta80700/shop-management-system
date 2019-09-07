#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<iostream.h>
#include<string.h>
#include<dos.h>
class item
{
	char itemname[20];
	int itemcode;
	float itemprice;
	char category[20];

	public:
	void input();
	void output();
	void showitem();
	float getitemprice()
	{
		return itemprice;
	}
	char* getitemcategory()
	{
		return category;
	}
	char* getitemname()
	{
		return itemname;
	}
	int getitemcode()
	{
		return itemcode;
	}
	item()
	{
		strcpy(itemname,'\0');
		itemcode=0;
		itemprice=0;
		strcpy(category,'\0');
	}
};
void item::showitem()
{
	int k1,k2,k3;
	k1=strlen(itemname);
	cout<<itemname;
	if(k1>4)
	{
		k1=24-k1;
		for(int i=0;i<k1;i++)
		cout<<" ";
		cout<<itemcode;
	}
	else
	{
		k1=20+4-k1;
		for(int i=0;i<k1;i++)
		cout<<" ";
		cout<<itemcode;
	}
	for(int i=0;i<21;i++)
	{
		cout<<" ";
	}
	cout<<itemprice<<endl;
}
int i,j,k,a,b,totalbill;
char choi,ans;
float total;
void item::input()
{
	cout<<endl<<"enter the item name: ";
	gets(itemname);
	cout<<endl<<"enter the item code: ";
	cin>>itemcode;
	cout<<endl<<"enter the item price: ";
	cin>>itemprice;
	cout<<endl<<"enter the category: ";
	gets(category);
}
void item::output()
{
	cout<<"Item name is: "<<itemname<<endl;
	cout<<"Item code is: "<<itemcode<<endl;
	cout<<"Item price is: "<<itemprice<<endl;
	cout<<"Item category is: "<<category<<endl;
}
void additem()
{
	fstream f1;
	item I;
	f1.open("item.dat",ios::out|ios::app|ios::binary);
	do
	{
		clrscr();
		cout<<"\t\t*************** ADD ITEM ***************"<<endl;
		cout<<endl;
		I.input();
		cout<<endl<<"Item added.."<<endl;
		f1.write((char*)&I,sizeof(I));
		cout<<endl<<"Want to add more?";
		cin>>choi;
	}while(choi=='y'||choi=='Y');
	f1.close();
}
void searchitem()
{
	D:
	int flag=0;
	char ch[30];
	fstream f1;
	cout<<"\t\t*************** SEARCH ITEM ***************"<<endl;
	cout<<endl;
	item I;
	cout<<endl<<"Enter the item name u want to search: ";
	gets(ch);
	f1.open("item.dat",ios::in|ios::binary|ios::app);
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
	{
		if(strcmp(ch,I.getitemname())==0)
		{
			cout<<endl<<"\t\t\tItem found..."<<endl;
			cout<<endl;
			I.output();
			flag=1;

		}
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
	if(flag==0)
	cout<<"Item not found!!!!!"<<endl;
	cout<<endl<<"Want to search for about more item: ";
	cin>>ans;
	if(ans=='y'||ans=='Y')
	{
		clrscr();
		goto D;
	}
}
void deleteitem()
{
	E:
	int flag=0;
	char ch[30];
	fstream f1,f2;
	item I;
	cout<<"\t\t*************** DELETE ITEM ***************"<<endl;
	cout<<endl<<"Enter the item name u want to delete: ";
	gets(ch);
	f1.open("item.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::app|ios::binary);
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
	{
		if(strcmp(ch,I.getitemname())!=0)
		{
			flag=1;
			f2.write((char*)&I,sizeof(I));
		}
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
	f2.close();
	if(flag==1)
	cout<<"Item deleted"<<endl;
	if(flag==0)
	cout<<"This item is not in your shop "<<endl;
	remove("item.dat");
	rename("temp.dat","item.dat");
	cout<<endl<<"Want to delete more item?: ";
	cin>>ans;
	if(ans=='y'||ans=='Y')
	{
		clrscr();
		goto E;
	}
}
void updateitem()
{
	F:
	fstream f1,f2;
	int flag=0;
	cout<<"\t\t*************** UPDATE ITEM ***************"<<endl;
	f1.open("item.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::app|ios::binary);
	char updatename[20];
	cout<<endl<<"Enter the name of the item you want to update: ";
	gets(updatename);
	item I;
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
	{
		if(strcmp(updatename,I.getitemname())==0)
		{
			clrscr();
			cout<<"\t\t\tEnter new updated info: "<<endl;
			cout<<endl;
			I.input();
			f2.write((char*)&I,sizeof(I));
			flag=1;
		}
		else
		f2.write((char*)&I,sizeof(I));
	f1.read((char*)&I,sizeof(I));
	}
	f1.close();
	f2.close();
	remove("item.dat");
	rename("temp.dat","item.dat");
	if(flag==1)
	cout<<"Item updated..."<<endl;
	else
	cout<<"This item doen't in our shop!!!!"<<endl;
	cout<<"Want to update more item?: ";
	cin>>ans;
	if(ans=='y'||ans=='Y')
	{
		clrscr();
		goto F;
	}
}
void showkitchen()
{
	fstream f1;
	item I;
	cout<<"\t*************** ITEMS IN SHOP RELATED TO KITCHEN ***************"<<endl;
	f1.open("item.dat",ios::in|ios::binary);
	f1.read((char*)&I,sizeof(I));
	cout<<endl<<"NAME.	                CODE.	                 PRICE."<<endl;
	while(!f1.eof())
	{
		if(strcmp(I.getitemcategory(),"kitchen")==0)
		I.showitem();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
void showstationary()
{
	fstream f1;
	item I;
	cout<<"\t*************** ITEMS IN SHOP RELATED TO STATIONARY ***************"<<endl;
	f1.open("item.dat",ios::in|ios::binary|ios::binary);
	f1.read((char*)&I,sizeof(I));
	cout<<endl<<"NAME.	                CODE.	                 PRICE."<<endl;
	while(!f1.eof())
	{
		if(strcmp(I.getitemcategory(),"stationary")==0)
		I.showitem();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
void showbathroom()
{
	fstream f1;
	cout<<"\t*************** ITEMS IN SHOP RELATED TO BATHROOM ***************"<<endl;
	item I;
	f1.open("item.dat",ios::in|ios::binary|ios::binary);
	f1.read((char*)&I,sizeof(I));
	cout<<endl<<"NAME.	                CODE.	                 PRICE."<<endl;
	while(!f1.eof())
	{
		if(strcmp(I.getitemcategory(),"bathroom")==0)
		I.showitem();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
void showgrocery()
{
	fstream f1;
	item I;
	cout<<"\t*************** ITEMS IN SHOP RELATED TO GROCERY ***************"<<endl;
	f1.open("item.dat",ios::in|ios::binary|ios::binary);
	f1.read((char*)&I,sizeof(I));
	cout<<endl<<"NAME.	                CODE.	                 PRICE."<<endl;
	while(!f1.eof())
	{
		if(strcmp(I.getitemcategory(),"grocery")==0)
		I.showitem();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
int total1=0,total2=0,total3=0,total4=0;
void calcbill1(int z)
{
	fstream f1;
	item I;
	f1.open("item.dat",ios::in|ios::app|ios::binary);
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
	{
		if(I.getitemcode()==z)
		total1+=I.getitemprice();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
void calcbill2(int z)
{
	fstream f1;
	item I;
	f1.open("item.dat",ios::in|ios::app|ios::binary);
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
	{
		if(I.getitemcode()==z)
		total2+=I.getitemprice();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
void calcbill3(int z)
{
	fstream f1;
	item I;
	f1.open("item.dat",ios::in|ios::app|ios::binary);
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
	{
		if(I.getitemcode()==z)
		total3+=I.getitemprice();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
void calcbill4(int z)
{
	fstream f1;
	item I;
	f1.open("item.dat",ios::in|ios::app|ios::binary);
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
	{
		if(I.getitemcode()==z)
		total4+=I.getitemprice();
		f1.read((char*)&I,sizeof(I));
	}
	f1.close();
}
void showbill(int h)
{
	fstream f1;
	item I;
	f1.open("item.dat",ios::in|ios::binary|ios::app);
	f1.read((char*)&I,sizeof(I));
	while(!f1.eof())
		{
			if(I.getitemcode()==h)
			{
				cout<<"\t\tyou have brought "<<I.getitemname()<<" of price: "<<I.getitemprice()<<endl;
				break;
			}
			f1.read((char*)&I,sizeof(I));
		}
	f1.close();
}

void main()
{
	clrscr();
	delay(650);
	cout<<"X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X"<<endl;
	cout<<"X *           *  * * * * *  *           * * *     * *     *     *   * * * * * X"<<endl;
	cout<<"X  *         *   *          *          *         *   *    * * * *   *         X"<<endl;
	cout<<"X   *   *   *    * * *      *         *         *     *   *  *  *   * * *     X"<<endl;
	cout<<"X    * * * *     *          *          *         *   *    *     *   *         X"<<endl;
	cout<<"X     *   *      * * * * *  * * * * *   * * *     * *     *     *   * * * * * X"<<endl;
	cout<<"X                                                                             X"<<endl;
	cout<<"X                                                                             X"<<endl;
	cout<<"X                             * * * * *    * *                                X"<<endl;
	cout<<"X                                 *       *   *                               X"<<endl;
	cout<<"X                                 *      *     *                              X"<<endl;
	cout<<"X                                 *       *   *                               X"<<endl;
	cout<<"X                                 *        * *                                X"<<endl;
	cout<<"X                                                                             X"<<endl;
	cout<<"X                                                                             X"<<endl;
	cout<<"X * * *      *     *     * * *   *    *        *     *     *     * * *  * * * X"<<endl;
	cout<<"X *    *    * *    * *   * *  * *    * *       * * * *    * *    *    *   *   X"<<endl;
	cout<<"X * * *    *   *   *  *  * *   *    *   *      *  *  *   *   *   * * *    *   X"<<endl;
	cout<<"X *    *  * * * *  *   * * *   *   * * * *     *     *  * * * *  *  *     *   X"<<endl;
	cout<<"X * * *  *       * *     * *   *  *       *    *     * *       * *    *   *   X"<<endl;
	cout<<"X                                                                             X"<<endl;
	cout<<"X                                               --- MADE BY HARSH GUPTA....   X"<<endl;
	cout<<"X                                                                             X"<<endl;
	cout<<"X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X"<<endl;
	delay(3500);
	clrscr();
	lb:
	cout<<"\t       *************** WELCOME TO OUR SHOP ***************"<<endl;
	A:
	for(a=0;a<8;a++)
	cout<<endl;
	cout<<"\t\t\tENTER:"<<endl;
	cout<<"\t\t\t1. LOG IN.."<<endl;
	cout<<"\t\t\t2. SHOW ALL ITEMS AND BUY.."<<endl;
	cout<<"\t\t\t3. EXIT.."<<endl;
	cout<<endl<<"\t\t\tENTER YOUR CHOICE: ";
	cin>>k;
	clrscr();
	char arr[10];
	switch(k)
	{
		case 1:
		a:
		cout<<"\t"<<endl;
		cout<<"ENTER PASSWORD: "<<endl;
		for(int i=0;i<10;i++)
		{
			arr[i]=getch();
			cout<<"*";
		}
		if(strcmp(arr,"harshgupta")==0)
		{
			clrscr();
			cout<<"LOGGING IN";
			for(a=0;a<5;a++)
			{
				cout<<".";
				delay(250);
			}
			clrscr();
			cout<<"\t\t*************** ADMIN FILE IS READY ***************";
			for(a=0;a<8;a++)
			cout<<endl;
			b:
			cout<<"\t\t\tWHAT DO YOU WANT TO DO?"<<endl;
			cout<<"\t\t\t1. Add items.."<<endl;
			cout<<"\t\t\t2. Search item.."<<endl;
			cout<<"\t\t\t3. Delete item.."<<endl;
			cout<<"\t\t\t4. Update item.."<<endl;
			cout<<"\t\t\t5. Logout.."<<endl;
			cout<<endl<<"\t\t\Enter your choice: ";
			cin>>a;
			switch(a)
			{
				case 1:
					clrscr();
					additem();
					clrscr();
					cout<<"Now enter again..."<<endl;
					goto b;
				case 2:
					clrscr();
					searchitem();
					clrscr();
					cout<<"Now enter again..."<<endl;
					goto b;
				case 3:
					clrscr();
					deleteitem();
					clrscr();
					cout<<"Now enter again..."<<endl;
					goto b;
				case 4:
					clrscr();
					updateitem();
					clrscr();
					cout<<"Now enter again..."<<endl;
					goto b;
				case 5:
					clrscr();
					cout<<"YOU ARE LOGGING OUT";
					for(a=0;a<5;a++)
					{
						cout<<".";
						delay(250);
					}
					clrscr();
					goto lb;

				default:
				cout<<"Wrong choice want to enter more?"<<endl;
				cin>>choi;
				if(choi=='y'||choi=='Y')
				goto b;
				else
				break;
			}
		}
		else
		{
			cout<<endl<<"Wrong password"<<endl;
			cout<<endl<<"Want to try again?: ";
			cin>>choi;
			if(choi=='y'||choi=='Y')
			goto a;
			else
			{
				clrscr();
				goto lb;
			}
		}
		break;
		case 2:
			int buyk[100],c;
			for(c=0;c<100;c++)
			buyk[c]=0;
			c=0;
			H:
			clrscr();
			G:
			cout<<"\t\t\tENTER THE CATEGORY"<<endl;
			cout<<"\t\t\t1. Kitchen"<<endl;
			cout<<"\t\t\t2. Bathroom"<<endl;
			cout<<"\t\t\t3. Stationary"<<endl;
			cout<<"\t\t\t4. Grocery"<<endl;
			cout<<"\t\t\t5. Exit"<<endl;
			cout<<endl<<"\t\t\tENTER YOUR CHOICE: ";
			cin>>b;
			char ans,q;
			switch(b)
			{
				case 1:
					clrscr();
					showkitchen();
					cout<<"Want to shop from this category?: ";
					cin>>q;
					if(q=='y'||q=='Y')
					{
						do
						{
							cout<<"Enter the item code you want to buy: ";
							cin>>buyk[c];
							calcbill1(buyk[c]);
							c++;
							cout<<"Want to buy more from this category: ";
							cin>>ans;
						}while(ans=='y'||ans=='Y');
					}
					cout<<"Want to see other categories?: ";
					cin>>ans;
					if(ans=='y'||ans=='Y')
					goto H;
					else
					break;

				case 2:
					clrscr();
					showbathroom();
					cout<<"Want to shop from this category?: ";
					cin>>q;
					if(q=='y'||q=='Y')
					{
						do
						{
							cout<<"Enter the item code you want to buy: ";
							cin>>buyk[c];
							calcbill2(buyk[c]);
							c++;
							cout<<"Want to buy more from this category: ";
							cin>>ans;
						}while(ans=='y'||ans=='Y');
					}
					cout<<"Want to see other categories?: ";
					cin>>ans;
					if(ans=='y'||ans=='Y')
					goto H;
					else
					break;

				case 3:
					clrscr();
					showstationary();
					cout<<"Want to shop from this category?: ";
					cin>>q;
					if(q=='y'||q=='Y')
					{
						do
						{
							cout<<"Enter the item code you want to buy: ";
							cin>>buyk[c];
							calcbill3(buyk[c]);
							c++;
							cout<<"Want to buy more from this category: ";
							cin>>ans;
						}while(ans=='y'||ans=='Y');
					}
					cout<<"Want to see other categories?: ";
					cin>>ans;
					if(ans=='y'||ans=='Y')
					goto H;
					else
					break;


				case 4:
					clrscr();
					showgrocery();
					cout<<"Want to shop from this category?: ";
					cin>>q;
					if(q=='y'||q=='Y')
					{
						do
						{
							cout<<"Enter the item code you want to buy: ";
							cin>>buyk[c];
							calcbill4(buyk[c]);
							c++;
							cout<<"Want to buy more from this category: ";
							cin>>ans;
						}while(ans=='y'||ans=='Y');
					}
					cout<<"Want to see other categories?: ";
					cin>>ans;
					if(ans=='y'||ans=='Y')
					goto H;
					else
					break;
				case 5:
					clrscr();
					cout<<"You are coming out of the categories";
					for(int i=0;i<8;i++)
					{
						cout<<".";
						delay(300);
					}
					clrscr();
					goto lb;
				default:
					clrscr();
					cout<<"Wrong choice enter again:"<<endl;
					delay(700);
					goto G;
			}
			clrscr();
			cout<<"\t\t*************** TOTAL BILL ***************"<<endl;
			cout<<endl;
			for(int j=0;j<c;j++)
			{
				showbill(buyk[j]);
			}
			totalbill=total1+total2+total3+total4;
			cout<<endl<<"\t\tTOTAL BILL IS: "<<totalbill<<endl;

			cout<<"Want to exit from the program :";
			totalbill=0;
			total1=total2=total3=total4=0;
			cin>>choi;
			clrscr();
			if(choi=='n'||choi=='N')
			goto lb;
			else
			break;
		case 3:
			break;
		default:
			clrscr();
			cout<<"Wrong choice enter again:"<<endl;
			delay(700);
			goto A;
	}
}
