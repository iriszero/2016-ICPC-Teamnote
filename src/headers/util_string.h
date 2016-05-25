#pragma once
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;



// 1. Suffix Array

#define MAX 500001
char str[MAX];
int n,gap,sa[MAX],pos[MAX],tmp[MAX],lcp[MAX];
// sa stores the sorted index of the suffixes
// pos stores the serial number of a index in the sorted sequence
bool sufCmp(int i, int j)
{
    if(pos[i]!=pos[j])
        return pos[i]<pos[j];
    i+=gap;
    j+=gap;
    return (i<n&&j<n)?pos[i]<pos[j]:i>j;
}
void buildSA()
{
    n=strlen(str);
    for(int i=0;i<n;i++)
        sa[i]=i,pos[i]=str[i];
    for(gap=1;;gap*=2)
    {
        sort(sa,sa+n,sufCmp);
        for(int i=0;i<n-1;i++)
            tmp[i+1]=tmp[i]+sufCmp(sa[i],sa[i+1]);
        for(int i=0;i<n;i++)
            pos[sa[i]]=tmp[i];
        if(tmp[n-1]==n-1)
            break;
    }
}
void buildLCP()
{
    for(int i=0,k=0;i<n;++i)
    {
        if(pos[i]==n-1)
            lcp[pos[i]]=0;
        else
        {
            for(int j=sa[pos[i]+1];str[i+k]==str[j+k];)
                k++;
            lcp[pos[i]]=k;
            if(k)
                k--;
        }
    }
}
/*Usage

    scanf("%s", str);
    buildSA();
    buildLCP();
    
    for (int i=0; i<n; i++) {
        printf("%d ", sa[i]+1);
    }
    printf("\nx ");
 
    for (int i=0; i<n-1; i++) {
        printf("%d ", lcp[i]);
    }
    printf("\n");
}

*/


// 2. Palindrome

#define MX 312345

int a[MX * 2];
char s[MX * 2];
char buf[MX];

vector<map<string, int>> v;

int min(int a, int b) {
    return (a<b) ? a : b;
}
int max(int a, int b) {
    return (a>b) ? a : b;
}
int actual_len(int len) {
 
    return len;
}
//Usage
/*
    scanf("%s", buf);
    
    //builld formatted string
    for (int i = 0; i<strlen(buf) - 1; i++) {
        s[2 * i] = buf[i];
        s[2 * i + 1] = '#';
    }
    s[2 * strlen(buf) - 2] = buf[strlen(buf)-1];
    s[2 * strlen(buf) - 1] = 0;
    
    
    int r = -1, p = -1;
    int len = 2 * strlen(buf) - 1;
    
    for (int i = 0; i<len; i++) {
        if (i <= r) a[i] = min(a[2 * p - i], r - i);
        else a[i] = 0;
        
        while (i-a[i]-1>=0 && i+a[i]+1 < strlen(s) && s[i - a[i] - 1] == s[i + a[i] + 1]) {
            a[i]++;
        }
        
        if (i + a[i] > r) {
            r = a[i] + i; p = i;
        }
    }
 
}
*/


// 3. Aho-corasick
#pragma once

#define ll long long
const int ALPHABETS = 27;
int toNum(char c) {
    return c – ‘a’;
}
struct node {
    node *children[ALPHABETS];
    int end;
    node() : end(false) { for (int i = 0; i < ALPHABETS; i++) children[i] = NULL; };
    node *fail;
    void insert(const char *key)
    {
        if (*key == 0)
            end = 1;
        else
        {
            int next = toNum(*key);
            if (children[next] == NULL)
                children[next] = new node();
            children[next]->insert(key + 1);
        }
    }
};

void FFC(node* root)
{
    queue<node*> q;
    root->fail = root;
    q.push(root);
    
    while (!q.empty()) {
        node* here = q.front(); q.pop();
        for (int edge = 0; edge< ALPHABETS; edge++)
        {
            node *child = here->children[edge];
            if (!child) continue;
            
            if (here == root) child->fail = root;
            else {
                node *t = here->fail;
                while (t != root && t->children[edge] == NULL)
                    t = t->fail;
                if (t->children[edge]) t = t->children[edge];
                child->fail = t;
            }
            child->end += child->fail->end;
            q.push(child);
        }
    }
}
int aho(const string &s, node *root) {
    int ret = 0;
    node *state = root;
    
    int size = s.size();
    for (int i = 0; i < size; i++) {
        int chr = toNum(s[i]);
        while (state != root && state->children[chr] == NULL)
            state = state->fail;
        if (state->children[chr]) state = state->children[chr];
        ret += state->end;
    }
    return ret;
}


// example of main
// return the number of string including { root } in dna
/*
node *root = new node();
string dna, marker;
cin >> dna >> marker;
list<string> lis;

for (int i = 0; i< m; i++)
for (int j = i; j < m; j++)
{
    reverse(marker.begin() + i, marker.begin() + j + 1);
    lis.push_back(marker);
    reverse(marker.begin() + i, marker.begin() + j + 1);
}

unique(lis.begin(), lis.end());

for (auto i : lis){
    root->insert(i.c_str());
}

FFC(root);

// RETURN //
return aho(dna, root);

*/

// 4. KMP

#pragma once

#include <vector>
#include <string>
using namespace std;
typedef vector<int> VI;

/*
 Returns: 0-based index of the first match
 Time: O(k) time
 usage: KMP(string, key);
 */

void buildTable(string& w, VI& t)
{
    t = VI(w.length());
    int i = 2, j = 0;
    t[0] = -1; t[1] = 0;
    
    while(i < w.length())
    {
        if(w[i-1] == w[j])
        {
            t[i] = j+1;
            i++;
            j++;
        }
        else if(j > 0)
            j = t[j];
        else { t[i] = 0; i++; }
    }
}

int KMP(string& s, string& w)
{
    int m = 0, i = 0;
    VI t;
    
    buildTable(w, t);
    while(m+i < s.length())
    {
        if(w[i] == s[m+i])
        {
            i++;
            if(i == w.length())
                return m;
        }
        else
        {
            m += i-t[i];
            if(i > 0) 
                i = t[i];
        }
    }  
    return s.length();
}