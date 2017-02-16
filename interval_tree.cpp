#include <bits/stdc++.h>
using namespace std;
struct node{
    int low, high, Max_Of_High;
    node *left, *right, *parent;
};
class I_Tree{
public:
    node *root;
    I_Tree(){
        root = NULL;
    }
    void insert(int l, int h){
        if(!root){
            root = new node();
            root->low = l;
            root->high = h;
            root->Max_Of_High = h;
            root->left = root->right = root->parent = NULL;
        }
        else{
            node *p = root;
            while(p){
                if(p->high<h){
                    p->high = h;
                }
                if(p->low < l && p->right){
                    p = p->right;
                }
                else if(p->low >= l && p->left){
                    p = p->left;
                }
                else
                    break;
            }
            node *q = new node();
            q->low = l;
            q->high = h;
            q->Max_Of_High = h;
            if(p->high<h)
                p->high = h;
            if(p->low < l){
                p->right = q;
            }
            else{
                p->left = q;
            }
            q->left = q->right = NULL;
            q->parent = p;
        }
    }

node *search(node *root, int l, int h){
        if (root == NULL)
            return NULL;
        if (root->low<=h && l<=root->high)
            return root;
        if (root->left != NULL && ((root->left)->Max_Of_High) >= l)
            return search(root->left, l, h);
        return search(root->right, l, h);
    }

    node* minNode(node* root){
        node *p = root;
        while (p->left != NULL)
            p = p->left;
        return p;
    }

    node* del_node(node* root, int key){
    if (root == NULL)
        return root;
    if (key < root->low)
        root->left = del_node(root->left, key);
    else if (key > root->low)
        root->right = del_node(root->right, key);
    else{
        node *p = root->parent;
        int maxleft = (root->left)->Max_Of_High, maxrt = (root->right)->Max_Of_High;
        if (root->left == NULL){
            node *temp = root->right;
            p->Max_Of_High = max(p->Max_Of_High, temp->Max_Of_High);
            return temp;
        }
        else if (root->right == NULL){
            node *temp = root->left;
            p->Max_Of_High = max(p->Max_Of_High, temp->Max_Of_High);
            return temp;
        }
        p->Max_Of_High = max(p->Max_Of_High, max((root->left)->Max_Of_High, (root->right)->Max_Of_High));
        node* temp = minNode(root->right);
        root->low = temp->low;
        root->high = temp->high;
        root->Max_Of_High =  max(maxleft, maxrt);
        root->right = del_node(root->right, temp->low);
    }
    return root;
}

};
int main(){

vector <pair<int, int> > p;
    int n, l, h;
    cin>>n;
    for(int i = 0; i<n; i++){
        cin>>l>>h;
        p.push_back(make_pair(l, h));
    }
    I_Tree T;
    for(int i = 0; i<n; i++){
        T.insert(p[i].first, p[i].second);
    }
    cin>>l>>h;
    node *match = T.search(T.root, l, h);
    if(match){
        cout<<"Interval overlapped"<<endl;
        cout<<"interval: "<<match->low<<" "<<match->high<<endl;
    }
    else{
        cout<<"Overlap interval not found"<<endl;
    }
    return 0;
}
