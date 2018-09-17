//
//  trendtracker.cpp
//  TT2
//
//  Created by Joshua Garza on 9/9/18.
//  Copyright © 2018 Joshua Garza. All rights reserved.
//

#include "trendtracker.h"

// Creates a Trendtracker containing hashtags
// found in the provided file.
// The file is promised to have the following format:
//
// string1
// string2
// ...
// stringN
//
// where string1 < string2 < ... < stringN
//
// Must run in O(n) time.
Trendtracker::Trendtracker(string filename){
    ifstream myFile;
    myFile.open(filename);
    string tag;
    

    if(myFile.fail()){
        cerr << "Error opening file" << endl;
        exit(1);
    }
    
    while( myFile >> tag){
        Entry e;
        e.hashtag = tag;
        e.pop = 0;
        E.push_back(e);
    }
    
    
    myFile.close();
}


// Return the number of hashtags in the Trendtracker.
//
// Must run in O(1) time.
int Trendtracker::size(){
    
    return static_cast<int>(E.size());
}

// Adds 1 to the total number times a hashtag has been tweeted.
// If the hashtag does not exist in TrendTracker, does nothing.
//
// Must run in O(log(n)) time.
void Trendtracker::tweeted(string ht){

    //uses the index that search returns to access the given hashtag and increase its popularity
    E[search(ht)].pop++;
    
    //check for duplicates
    bool duplicate = false;
    for(int i = 0; i < S.size(); i++){
        if(S[i] == search(ht))
            duplicate = true;
    }
    if(!duplicate)
        S.push_back(search(ht));
    
    
    //sort the elements of S by the pops in the entrys they refer to(from large to small)
    
    //insertion sort
    for(int i = 0; i < S.size(); i++){
        int j = i;
        while(j > 0 && E[S[j]].pop > E[S[j-1]].pop){
            int temp = S[j-1];
            S[j-1] = S[j];
            S[j] = temp;
            j--;
        }
    }
    
    //if s has more than 3 elements, remove the last one
    if(S.size() > 3)
        S.pop_back();
    
    //printS();
}



// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
//
// Must run in O(log(n)) time.
int Trendtracker::popularity(string name){
    if(search(name) != -1)
        return E[search(name)].pop;
    return -1;
}

// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
//
// Must run in O(1) time.

string Trendtracker:: top_trend(){
    if(E.size() == 0)
        return "";
    return E[S[0]].hashtag;
   
}

// Fills the provided vector with the 3 most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(1) time.

void Trendtracker::top_three_trends(vector<string> &T){
    T.clear();

    if(E.size() == 1) //test case for tiny.txt
        T.push_back(E[0].hashtag);
    else{
        if(S.size() == 0){
            T.push_back(E[0].hashtag);
            T.push_back(E[1].hashtag);
            T.push_back(E[1].hashtag);
        }
        else if(S.size() == 1){
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[1].hashtag);
            T.push_back(E[2].hashtag);
        }
        else if(S.size() == 2){
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[S[1]].hashtag);
            T.push_back(E[2].hashtag);

        }else if(S.size() == 3){
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[S[1]].hashtag);
            T.push_back(E[S[2]].hashtag);
        }
    }
    
}


// Optional helper method.
// Returns the index of E containing an Entry with hashtag ht.
// If no such hashtag is found, returns -1.
//
// Should run in O(log(n)).
int Trendtracker::search(string ht){
    int low = 0;
    int high = E.size() - 1;
    
    while(low <= high){
        int mid = ((high + low)/2);
        
        if(E[mid].hashtag < ht)
            low = mid + 1;
        else if(E[mid].hashtag > ht)
            high = mid - 1;
        else
            return mid; //found
        
    }
    
    return -1;
}


            
            
            
            
            
            
            
            
