#include<bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0);cin.tie(0);
#define LL long long int
#define pb push_back
#define mp make_pair
#define pp pair<int,int>
#define ff first
#define ss second
using namespace std;
class priority
{
public:
  bool operator()(const pair<int,int> &p1,const pair<int,int> &p2)
  {
    p1.ff>p2.ff;
  }
};
class node
{
    int n; // node number
    string type; // type of node
 //   int sd; // school distance
    int pd,pn; // police station distance
    int hd,hn; // hospital distance
    int mk,mn; // market distance
    int sector;//sector no.
    string color;
   public:
    node()
    {
        n=mk=pd=hd=mn=pn=hn=0;
        sector=0;
        type="";
        color="";
    }
    node(int i)
    {
    	n=i;
       n=mk=pd=hd=mn=pn=hn=0;
        sector=0;
        type="";
        color="";

    }
    void set_pd(int a,int t)
    {
      pd=a;
      pn=t;

    }
    void set_hd(int a,int t)
    {
      hd=a;
      hn=t;
    }
    void set_mk(int a,int t)
    {
      mk=a;
      mn=t;
    }
    void set_type(string a)
    {
    	type=a;
    }
    void set_color(string s)
    {
      color=s;
    }
    void set_sector(int s)
    {
      sector=s;
    }
    string get_type()
    {
    	return type;
    }
    int get_sector()
    {
      return sector;
    }
    string get_color()
    {
      return color;
    }
    int get_pd()
    {
      return pd;

    }
    int get_mk()
    {
      return mk;
    }
    int get_hd()
    {
      return hd;
    }
    int getpn()
    {
      return pn;
    }
    int gethn()
    {
      return hn;
    }
    int getmn()
    {
      return mn;
    }

};

//////////// declaration of data structures
vector < pair< int,int > > v[101];
node *block[101];
//////////// main code starts from here




void blueprint()
{
	int i,j;
	for(i=1;i<=10;i++)
	{
  	v[0].pb(mp(i,1));
    v[1].pb(pp(0,INT_MAX));
  }
    j=1;
	for(i=1;i<=90;i++)
	{
		
		v[i].pb(mp(i+10,1));
		v[i+10].pb(mp(i,1));
    if(i%10==0)
    {
		  v[i-9].pb(mp(i,i/10));
		  v[i].pb(mp(i-9,i/10));
    }
    else
    {
      v[i+1].pb(mp(i,i/10 +1));
      v[i].pb(mp(i+1,i/10 +1));
    }
      
	}

}

vector<int> d[101];
void cal_distances(int s)
{
     priority_queue <pp,vector<pp>,greater<pp> > pq;
  for(int i=0;i<=100;i++)
    d[s].pb(INT_MAX);
  d[s][s]=0;
  pq.push(pp(d[s][s],s));
  while(!pq.empty())
  {
    int u=pq.top().second;
    pq.pop();
    int size=v[u].size();
    for(int i=0;i<size;i++)
    {
      int v1=v[u][i].ff;
      int w=v[u][i].ss;
      if(d[s][v1]>d[s][u]+w&&d[s][u]+w>0)
      {
        d[s][v1]=d[s][u]+w;
        pq.push(pp(d[s][v1],v1));
      }
    }


  }
}

void djikstra(int s,int p[])
{
  int d[101];
  for(int i=0;i<=100;i++)
    d[i]=INT_MAX;
  priority_queue<pp,vector<pp> ,priority> pq;
  d[s]=0;
  pq.push(pp(d[s],s));
  while(!pq.empty())
  {
    int u=pq.top().ss;
    pq.pop();
    vector<pp> ::iterator i;
    for( i=v[u].begin();i!=v[u].end();i++)
    {
      int v1=i->ff;
      int w=i->ss;
     // cout<<d[u]+w<<endl;
      if(d[v1]>d[u]+w&&d[u]+w>0)
      {
        p[v1]=u;
        d[v1]=d[u]+w;
        pq.push(pp(d[v1],v1));
      }
    }
  }
 // for(int i=1;i<=100;i++)
   // cout<<d[i]<<endl;
}

int get_roadnumber(int s,int d)
{
  if(abs(d-s)<10)
    return d/10+1;
  else if(abs(d-s)==10)
    return d%10+10;
}


void directions(int s,int d)
{
  int parent[101];
  for(int i=0;i<=100;i++)
    parent[i]=-1;
  parent[s]=s;
  djikstra(s,parent);
  stack<int> st;
  while(d!=s)
  {
    st.push(d);
    d=parent[d];
  }
  int prev=s;
  while(!st.empty())
  {
        int curr=st.top();
        st.pop();
        int g=get_roadnumber(prev,curr);
        cout<<"Move from Place "<<prev<<" to "<<curr<<" by road "<<g<<endl;
        prev=curr;
  }
  cout<<"Destination reached"<<endl;

}


void cal()
{
  for(int i=0;i<=100;i++)
  {
    cal_distances(i);
  }
}
vector<int> sec[6];




struct s
{
  bool p;
  bool h;
  bool mk;
  s()
  {
    p=h=mk=false;
  }
  bool check()
  {
     if(p==true && h==true && mk==true)
      return true;
     else
      return false;
  }
};
s sector[6];




void allocate_Sectors()
{
  for(int i=1;i<=5;i++)
  {
     int j=2*i-1;
     int k=2*i;
     while(j<=100&&k<=100)
     {
       block[j]->set_sector(i);
       sec[i].push_back(j);
       sec[i].push_back(k);
       block[k]->set_sector(i);
       j=j+10;
       k=k+10;
     }

  }
}



int checkp(int i)
{
  int size=v[i].size();
  for(int j=0;j<size;j++)
  {
    if(block[v[i][j].ff]->get_color()=="yellow")
      return -1;
    
  }
  return 1;
}



   
int checkhp(int i)
{
  int size=v[i].size();
  for(int j=0;j<size;j++)
  {
    if(block[v[i][j].ff]->get_color()=="white")
      return -1;
    
  }
  return 1;
}




int checkmk(int i)
{

  int size=v[i].size();
  for(int j=0;j<size;j++)
  {
    if(block[v[i][j].ff]->get_color()=="red")
      return -1;
    
  }
  return 1;
}



priority_queue<pp ,vector<pp>,greater<pp> > *q;
void shortest(int i,int st)
{
  q=new priority_queue<pp, vector<pp> ,greater<pp> >();
  for(int j=1;j<=100;j++)
  {
      if((block[j]->get_type()=="")&&(block[j]->get_sector()==st))
      q->push(pp(d[i][j],j));      
  }
}

void assign_police(int i,int st)
{
   shortest(i,st);
    while(!q->empty())
    {
          pp t=q->top();
          q->pop();
          int v=t.ss;
          if(checkp(v)==1)
          {
            sector[st].p=true;
            block[v]->set_color("yellow");
            block[v]->set_type("police");
            break;
          }
    }

}

void assign_hospital(int i,int st)
{
  shortest(i,st);
    while(!q->empty())
    {
          pp t=q->top();
          q->pop();
          int v=t.ss;
          if(checkhp(v)==1)
          {
            sector[st].h=true;
            block[v]->set_color("white");
            block[v]->set_type("hospital");
            break;
          }
    }
}

void assign_market(int i,int st)
{
  shortest(i,st);
    while(!q->empty())
    {
          pp t=q->top();
          int v=t.ss;
          q->pop();
          if(checkmk(v)==1)
          {
            sector[st].mk=true;
            block[v]->set_color("red");
            block[v]->set_type("market");
            break;
          }
    }
}
void get(int k,int *a,int *b,int *c,int *d1,int *e,int *f)
{
  int minh=INT_MAX;
  int minmk=INT_MAX;
  int minp=INT_MAX;
  for(int i=1;i<=100;i++)
  {
    if(d[k][i]<minp&&block[i]->get_type()=="police")
    {
      minp=d[k][i];
      *a=minp;
      *d1=i;
    }
     if(d[k][i]<minh&&block[i]->get_type()=="hospital")
    {
      minh=d[k][i];
      *b=minh;
      *e=i;
    }
     if(d[k][i]<minmk&&block[i]->get_type()=="market")
    {
      minmk=d[k][i];
      *c=minmk;
      *f=i;
    }

  }
}
void store_distances()
{
  for(int i=1;i<=100;i++)
  {
    int a=0,b=0,c=0,d1,e,f;
    if(block[i]->get_type()=="Appartment"||block[i]->get_type()=="workplace")
    {
            get(i,&a,&b,&c,&d1,&e,&f);
            block[i]->set_mk(c,f);
            block[i]->set_hd(b,e);
            block[i]->set_pd(a,d1);
    }
  }
}



void assign()
{
  for(int i=1;i<=100;i++)
  {
    if(block[i]->get_type()=="Appartment"&&sector[block[i]->get_sector()].check()==false)
    {
      if(sector[block[i]->get_sector()].p==false)
      {
        assign_police(i,block[i]->get_sector());
      }
      if(sector[block[i]->get_sector()].h==false)
      {
        assign_hospital(i,block[i]->get_sector());
      }
      if(sector[block[i]->get_sector()].mk==false)
      {
        assign_market(i,block[i]->get_sector());
      }
    }
    else if(block[i]->get_type()=="")
      block[i]->set_type("workplace");
  }
}
void print()
{
  
    printf("%s","Sector 1");
    printf("%15s","Sector 2");
    printf("%15s","Sector 3");
    printf("%15s","Sector 4");
    printf("%15s","Sector 5");
    cout<<endl;
    for(int i=0;i<20;i++)
    {
      cout<<sec[1][i]<<"."<<block[sec[1][i]]->get_type();
      int n=block[sec[1][i]]->get_type().length();
      n=n+3;
       if(n==9)
        printf("%6c",' ');
       else if(n==13)
        printf("%2c",' ');
      else if(n==12)
        printf("%3c",' ');
       else
        printf("%3c",' ');
      cout<<sec[2][i]<<"."<<block[sec[2][i]]->get_type();
       n=block[sec[2][i]]->get_type().length();
      n=n+3;
       if(n==9)
        printf("%6c",' ');
       else if(n==13)
        printf("%2c",' ');
      else if(n==12)
        printf("%3c",' ');
       else
        printf("%3c",' ');
      cout<<sec[3][i]<<"."<<block[sec[3][i]]->get_type();
       n=block[sec[3][i]]->get_type().length();
      n=n+3;
       if(n==9)
        printf("%6c",' ');
       else if(n==13)
        printf("%2c",' ');
       else if(n==12)
        printf("%3c",' ');
       else
        printf("%3c",' ');
      
      cout<<sec[4][i]<<"."<<block[sec[4][i]]->get_type();
       n=block[sec[4][i]]->get_type().length();
      n=n+3;
       if(n==9)
        printf("%6c",' ');
       else if(n==13)
        printf("%2c",' ');
      else if(n==12)
        printf("%3c",' ');
       else
        printf("%3c",' ');
      cout<<sec[5][i]<<"."<<block[sec[5][i]]->get_type();
      cout<<endl;
    }
  cout<<"\n";
}
void findpolice(int i)
{
   int p=block[i]->getpn();
   cout<<"Minimum distance from police station is "<<block[i]->get_pd()<<endl;
   directions(i,p);

}
void findhospital(int i)
{
   int p=block[i]->gethn();
   cout<<"Minimum distance from hospital is "<<block[i]->get_hd()<<endl;
   directions(i,p);

}
void findmarket(int i)
{
   int p=block[i]->getmn();
   cout<<"Minimum distance from market is "<<block[i]->get_mk()<<endl;
   directions(i,p);

}
void find()
{
  cout<<"enter place number "<<endl;
  int i;
  cin>>i;
  while(block[i]->get_type()!="Appartment"&&block[i]->get_type()!="workplace")
  {
     cout<<"Enter again "<<endl;
     cin>>i;
  }
  int flag=0;
  while(1)
  {
    fflush(stdin);
    cout<<"1. Find nearest police station "<<endl;
    cout<<"2. Find nearest hospital "<<endl;
    cout<<"3. Find nearest market"<<endl;
    cout<<"4. Back to main menu"<<endl;
    int x;
    cin>>x;
    switch(x)
    {
      case 1:
      fflush(stdin);
      findpolice(i);
      break;

      case 2:
      fflush(stdin);
      findhospital(i);
      break;

      case 3:
      fflush(stdin);
      findmarket(i);
      break;

      case 4:
      fflush(stdin);
      flag=1;
      break;

      default : cout<<"Enter valid input\n";
                  break;
    }
    if(flag==1)
      break;

  }

}
int gd()
{
  int a,b;
  cout<<"Enter source and Destination"<<endl;
  cin>>a>>b;
  cout<<"Minimum distance is "<<d[a][b]<<endl;
  directions(a,b);
}
void places()
{  cout<<"Enter a location\n";
  int i;
  cin>>i;
  cout<<"This is "<<block[i]->get_type()<<endl;
  cout<<"Sector no "<<block[i]->get_sector()<<endl;
  if(block[i]->get_type()=="Appartment"||block[i]->get_type()=="workplace")
  {
    cout<<"Nearest police station is at distance "<<block[i]->get_pd()<<endl;
    cout<<"Nearest hospital station is at distance "<<block[i]->get_hd()<<endl;
    cout<<"Nearest market station is at distance "<<block[i]->get_mk()<<endl;
  }
  
  cout<<"\n";
}
int main()
{
    srand(time(NULL));
    map<int,int> m;
    int p;
    int i1;
    for(i1=0;i1<=100;i1++)
       block[i1]=new node(i1);
     blueprint();
     allocate_Sectors();
     cal();
    for(int i=1;i<=70;)
    {
      int t=rand()%85;
      if(m[t]==0)
      {
        block[t]->set_type("Appartment");
        i++;
        m[t]=1;
      }
    }
    assign();
    store_distances();
    int flag=0;
    while(1)
    {
      fflush(stdin);
    cout<<"1.  Print City  "<<endl;
    cout<<"2.  Location details "<<endl;
    cout<<"3.  Get Directions  "<<endl;
    cout<<"4.  Find   "<<endl;
    cout<<"5.  Exit"<<endl;
    int x;
    cin>>x;
    switch(x)
    {
      case 1:
      fflush(stdin);
      print();
      break;

      case 2:
      fflush(stdin);
      places();
      break;

      case 3:
      fflush(stdin);
      gd();
      break;

      case 4:
      fflush(stdin);
      find();
      break;
 
      case 5:
      fflush(stdin);
      flag=1;
      break;
      default : cout<<"Enter a valid input\n";
                break;
    }
    if(flag==1)
      break;
    }
    return 0;
}
// taj.alam@jiit.ac.in