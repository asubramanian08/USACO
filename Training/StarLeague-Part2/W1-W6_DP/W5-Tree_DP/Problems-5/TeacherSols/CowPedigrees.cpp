//Cow Pedigrees. USACO Training 2.3
#include <iostream>

#define MOD 9901

using namespace std;

//ifstream cin ("nocows.in");
//ofstream cout("nocows.out");

int table[101][202],N,K,c;
int smalltrees[101][202];

int main() 
{
    cin >> N >> K;
	
    table[1][1]=1;
    for (int i=2;i<=K;i++) 
	{
        for (int j=1;j<=N;j+=2)
            for (int k=1;k<=j-1-k;k+=2) 
			{
                if (k!=j-1-k) c=2; else c=1;    
                table[i][j]+=c*(
                        smalltrees[i-2][k]*table[i-1][j-1-k]  	// left subtree smaller than i-1
                        +table[i-1][k]*smalltrees[i-2][j-1-k]  	// right smaller
                        +table[i-1][k]*table[i-1][j-1-k]);		// both i-1
                table[i][j]%=MOD;
            }
        for (int k=0;k<=N;k++) 
		{   // we ensure that smalltrees[i-2][j] in the next i
            smalltrees[i-1][k] += table[i-1][k] + smalltrees[i-2][k]; 	// iteration contains the number
            smalltrees[i-1][k] %= MOD;           						// of trees smaller than i-1 and with j nodes
        }
    }
    
    cout << table[K][N] << endl;
}
 