#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include "bst.h"
#include "db.h"

using namespace std;


const char* const short_opt = ":ht:s:i:o:";
const struct option long_opt[] = {
    {"help",           0, NULL, 'h'},
    {"test",           1, NULL, 't'},
    {"seed",           1, NULL, 's'},
    {"input",          1, NULL, 'i'},
    {"output",         1, NULL, 'o'},
    {NULL,             0, NULL,  0}
};


void usage(char* argv);
void unittest_bst(unsigned int n, unsigned int seed, ostream& to,
                  unsigned int remain);
bool read_db(const string file_name, vector<string>& firsts, 
             vector<string>& lasts, vector<unsigned int>& ages);
void create_db(BST& db, const vector<string> f_, const vector<string> l_, 
               const vector<unsigned int> a_);
bool unittest_db(string ifile_name, string ofile_name);

/* Main function 
 */
int main(int argc, char **argv)
{
    int c = 0;
    string test = "0";
    string seed_str = "0"; 
    string ifile_name;
    string ofile_name;

    if(argc < 2) {
        usage(argv[0]);
        return 0;
    }

    while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        switch(c) {
            case 'h':
                usage(argv[0]);
                return 0;
            case 't':
                test = optarg;
                break;
            case 's':
                seed_str = optarg;
                break;
            case 'i':
                ifile_name = optarg;
                break;
            case 'o':
                ofile_name = optarg;
                break;
            default:
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Unit Test
    int num_test = stoi(test);
    if(num_test > 0) {
        int seed = stoi(seed_str);
        unittest_bst(num_test, seed, cout, 5);
    }

    // Check if input and output files were specified
    if(ifile_name.empty() || ofile_name.empty()) {
        usage(argv[0]);
        return -1;
    } 

    if(!unittest_db(ifile_name, ofile_name)) {
        return -1;
    }

    return 0;
}


/* Print information on how to properly use this program
 */
void usage(char* call)
{
    cout << "Usage: " << call << endl;
    cout << "Options:" << endl;
    cout << "\t-h or --help            Display this information" << endl;
    cout << "\t-t or --test n          BST Unit Test with n elements" << endl;
    cout << "\t-s or --seed s          Rand # seed value" << endl;
    cout << "\t-i or --input ifname    Input file" << endl;
    cout << "\t-o or --output ofname   Output file" << endl;
}

void unittest_bst(unsigned int n, unsigned int seed, ostream& to, 
                  unsigned int remain)
{
    to << "Unit Test for baseline BST implementation" << endl;
    srand(seed);
    vector<int> keys(n);
    for(unsigned int i = 0; i < keys.size(); i++) {
        keys[i] = rand() % 100;
    }
    int num_keys = keys.size();

    /* or you can specify keys manually */
    /* Make sure this is commented out for the final submission */
    #if 0
    keys[0] = 15;
    keys[1] = 10;
    keys[2] = 20;
    keys[3] = 8;
    keys[4] = 12;
    keys[5] = 16;
    keys[6] = 25;
    num_keys = 7;
    keys.resize(num_keys);
    keys.shrink_to_fit();
    #endif
    #if 0
    keys[0] = 100;
    keys[1] = 1;
    keys[2] = 150;
    keys[3] = 101;
    keys[4] = 23;
    keys[5] = 47;
    num_keys = 6;
    keys.resize(num_keys);
    keys.shrink_to_fit();
    #endif


    // Unsorted numbers
    to << "Input: " << endl;
    for(int i = 0; i < num_keys; i++) {
        to << keys[i] << " ";
    }
    to << endl;

    // Sorted numbers should look like...
    vector<int> tmp = keys;
    sort(tmp.begin(), tmp.end());
    to << "Sorted input: " << endl;
    for(int i = 0; i < num_keys; i++) {
        to << tmp[i] << " ";
    }
    to << endl;


    // insert_node() test
    Node** nodes = new Node*[num_keys];
    BST my_BST;
    for(int i = 0; i < num_keys; i++) {
        nodes[i] = new Node(keys[i]);
        my_BST.insert_node(nodes[i]);
    }

    // tree_min() and tree_max() test
    to << "----------" << endl;
    to << "BST min: " << my_BST.tree_min()->get_key() << endl;
    to << "BST max: " << my_BST.tree_max()->get_key() << endl;
    to << "----------" << endl;

    // walk() test
    to << "----------" << endl;
    to << "BST walk" << endl;
    my_BST.walk(to);
    to << "----------" << endl;

    // get_pred() and get_succ() test
    to << "----------" << endl;
    to << "Predecessor/Successor" << endl;
    for(int i = 0; i < num_keys; i++) {
        
        to << nodes[i]->get_key();
        if(my_BST.get_pred(nodes[i]) != nullptr) {
             to << " pred: " << my_BST.get_pred(nodes[i])->get_key();
        } else {
             to << " pred: " << "none";
        }
        if(my_BST.get_succ(nodes[i]) != nullptr) {
             to << " succ: " << my_BST.get_succ(nodes[i])->get_key() << endl;
        } else {
             to << " succ: " << "none" << endl;;
        }

    }
    to << "----------" << endl;


    // tree_search() test
    to << "----------" << endl;
    to << "tree_search() with fake keys" << endl;
    for(int i = 0; i < num_keys; i++) {
        Node* tmp = my_BST.tree_search(keys[i] + 1);
        if(tmp != nullptr) {
            to << "Found " << tmp->get_key() << endl;
        } else {
            to << keys[i] + 1 << " was not found" << endl;
        }
    }
    to << "----------" << endl;

    
    // tree_search() and delete_node() test
    to << "----------" << endl;
    to << "tree_search() and delete_node()" << endl;
    for(unsigned int i = 0; i < num_keys - remain; i++) {
        to << "---- deleting " << keys[i] << "-----" << endl;
        Node* tmp = my_BST.tree_search(keys[i]);
        if(tmp != nullptr) {
            my_BST.delete_node(tmp);
            my_BST.walk(to);
        } else {
            to << keys[i] << " was not found" << endl;
        }
    }
    to << "----------" << endl;

    // Cleanup
    delete [] nodes;

}

bool read_db(const string file_name, vector<string>& firsts, 
             vector<string>& lasts, vector<unsigned int>& ages)
{
    bool ret = true;
    ifstream inFile(file_name);

    string line;
    while(getline(inFile, line)) {
        stringstream sline(line);
        string token;
        getline(sline, token, ' ');
        firsts.push_back(token);
        getline(sline, token, ' ');
        lasts.push_back(token);
        getline(sline, token, ' ');
        int age_;
        stringstream(token) >> age_;
        ages.push_back(age_);
    }
    if(!((firsts.size() == lasts.size()) && (firsts.size() == ages.size()))) {
        cerr << "List sizes are not equal" << endl;
        ret = false;
    } 
    inFile.close();

    return ret;
}

void create_db(BST& db, const vector<string> f_, const vector<string> l_, 
               const vector<unsigned int> a_)
{
    for(unsigned int i = 0; i < f_.size(); i++) {
        SNode* st = new SNode(f_[i], l_[i], a_[i]);
        db.insert_node(st);
    }
}


bool unittest_db(string ifile_name, string ofile_name)
{
    vector<string> first_names;
    vector<string> last_names;
    vector<unsigned int> ages;
    if(!read_db(ifile_name, first_names, last_names, ages)) {
        return false;
    }
    
    BST student_db;
    create_db(student_db, first_names, last_names, ages); 
    ofstream outFile(ofile_name);

    outFile << "-------------------------------------------------" << endl;
    student_db.walk(outFile);
    outFile << "-------------------------------------------------" << endl;
    outFile << "First student ever: " << endl;
    student_db.tree_min()->print_info(outFile);
    outFile << "Last student to join: " << endl;
    student_db.tree_max()->print_info(outFile);
    unsigned int n = 36;
    outFile << "Information on student: " << n << endl;
    student_db.tree_search(n)->print_info(outFile);
    outFile << "Removing student...";    
    student_db.delete_node(student_db.tree_search(n));
    SNode* tmp = (SNode*) student_db.tree_search(n);
    if(tmp == nullptr) {
        outFile << "student successfully removed" << endl;
    } else {
        outFile << "error removing student" << endl;
    }
    outFile << "-------------------------------------------------" << endl;
    student_db.walk(outFile);
    outFile << "-------------------------------------------------" << endl;

    outFile.close();
   
    return true;
}
