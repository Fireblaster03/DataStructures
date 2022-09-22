#include "../include/json.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <queue>

using std::cout;
using std::endl;


int main(int argc, char **argv) {

  //
  // Recomendation:  Define your associative containers here.
  // Use enough containers such that you only need to parse the input data one
  // time in a "single pass".

  std::map<std::string, int> authorData;
  
  std::multimap<std::string, size_t> utcInfo;

  std::map<std::string, std::string> commentInfo;

  std::map<std::string, size_t> commentCharacterCount;

  // vector that will be 
  
  std::map<std::string, std::vector<std::string>> subredditInfo;
  //std::map<std::string, std::vector<std::string>>::iterator subRedditInfoIterator;
  std::map<std::string, int> numberRedditsPosted;

  std::map<std::string, std::vector<std::string>> authorInfo;
  //std::map<std::string, std::vector<std::string>>::iterator authorInfoIterator;
  std::map<std::string, int> numberAuthors;
  //
  // Parse the reddit ndjson input file
  std::ifstream ifs("../data/RC_2019-02-01_trimmed.ndjson");
  //std::ifstream ifs("test.json");
  std::string line;
  size_t record_count{0};
  
  while (std::getline(ifs, line)) {
    record_count++;

    // Use this to help test faster with fewer records
    if(record_count == 100000) break;

    //
    // Important fields to use
    auto json = nlohmann::json::parse(line);
    std::string author = json["author"];
    std::string subreddit = json["subreddit"];
    std::string body = json["body"];
    std::string id = json["id"];
    std::string parent_id = json["parent_id"];
    size_t created_utc = json["created_utc"];
    size_t score = json["score"];

    //
    // Add data to associative containers using the fields above
    // .....

    // authorData map used for first 3 questions
    if(authorData.find(author) == authorData.end()) {
      authorData.insert({author, 1});
    }
    else {
      authorData[author] += 1;
    }
    // adding all the utc info to utcInfo map
    utcInfo.insert(std::pair<std::string, size_t>(author, created_utc));

    commentInfo.insert(std::pair<std::string, std::string>(body, author));



    if(commentCharacterCount.find(author) == commentCharacterCount.end()) {
      commentCharacterCount.insert({author, body.size()});
    }
    else {
      commentCharacterCount[author] += body.size();
    }

    // insert vector of subreddits that author wrote in
    // increment number of subreddits that author wrote in a different map
	if (subredditInfo.find(author) == subredditInfo.end()) {
		
		numberRedditsPosted.insert({author, 1});
		//cout << author << endl;
		std::vector<std::string> authorSubreddits;
		// inserting current subreddit into vector
		authorSubreddits.push_back(subreddit);

		// inserting vector and author into map
		subredditInfo.insert({author, authorSubreddits});
	}
	else {

        //std::vector<std::string> authorSubredditsChecker;
        // new vector that will be used to compare old subreddits to see if new subreddit is added
		// printing out what is in the vector right now which should only be one element right now
        if(std::find(subredditInfo[author].begin(), subredditInfo[author].end(), subreddit) == subredditInfo[author].end()) {
			subredditInfo[author].insert(subredditInfo[author].begin(), subreddit);
			numberRedditsPosted[author]+=1;
        
        }
    } 

	if (authorInfo.find(subreddit) == authorInfo.end()) {
		
		numberAuthors.insert({subreddit, 1});
		//cout << author << endl;
		std::vector<std::string> subredditTotalAuthors;
		// inserting current subreddit into vector
		subredditTotalAuthors.push_back(author);

		// inserting vector and author into map
		authorInfo.insert({subreddit, subredditTotalAuthors});
	}
	else {

        //std::vector<std::string> authorSubredditsChecker;
        // new vector that will be used to compare old subreddits to see if new subreddit is added
		// printing out what is in the vector right now which should only be one element right now
        if(std::find(authorInfo[subreddit].begin(), authorInfo[subreddit].end(), author) == authorInfo[subreddit].end()) {
			authorInfo[subreddit].insert(authorInfo[subreddit].begin(), author);
			numberAuthors[subreddit]+=1;
        
        }
    } 


	/*if(numberAuthors.find(subreddit) == numberAuthors.end()) {
      numberAuthors.insert({author, 1});
    }
    else {
      authorData[author] += 1;
    }*/
  }
  cout << record_count << " records parsed." << endl;

  //////////////////////////////////////////////////////////////////////////////
  // Deliverables:  Answer the following 10 questions by cout'ing to console  //
  //////////////////////////////////////////////////////////////////////////////

  //
  // Notes:
  // When ties in authors or subreddits exists, lexigraphically sort by string.
  //

  //
  // 1. Who are the Top 10 most prolific authors (most number of comments)?
    
    /*
      1. get the data of the second value in the map
      2. loop that will compare each value as you go to the next map pair
      3. remove the biggest value and return it at the end
      4. do this 10 times or reverse from the end to remove/return last 10 elements(highest elements)
    */

  /*std::pair<std::string, int> findEntryWithLargestValue(std::map<std::string, int> sampleMap)
  {*/
  std::vector<std::string> mostProlificAuthors; 
	for (int i = 0; i < 10; i++) {
		// function gives singular highest value
		std::map<std::string, int>::iterator currentEntry; 
		//std::map<std::string, int>::value_compare mycomp = authorData.value_comp();
		std::pair<std::string, int> storedValue;
		int mostComments = authorData.begin()->second;
		for (currentEntry = authorData.begin(); 
			currentEntry != authorData.end(); ++currentEntry) {
		//mycomp((*currentEntry++)->second, mostComments)); //next authorData->first)
			if(currentEntry->second > mostComments && std::find(mostProlificAuthors.begin(), mostProlificAuthors.end(), currentEntry->first) == mostProlificAuthors.end()) {
			   
				mostComments = currentEntry->second;
				storedValue.first = currentEntry->first;
				storedValue.second = currentEntry->second;
			}
		}
		// if statement checks if author already in vector
		mostProlificAuthors.insert(mostProlificAuthors.begin(), storedValue.first);
	}
    for(int i = 0; i < mostProlificAuthors.size(); i++) {
		cout << 10-i << " most prolific author is " << mostProlificAuthors[i] << endl;
	}
  

  //
  // 2. How many authors only comment once?
    std::vector<std::string> singleComment;
	std::map<std::string, int>::iterator singleCommentIterator; 
    for (singleCommentIterator = authorData.begin(); singleCommentIterator != authorData.end(); ++singleCommentIterator) {
      if(singleCommentIterator->second == 1) {
        singleComment.push_back(singleCommentIterator->first);
      }
    }
	
	cout << singleComment.size() - 1 << " authors only comment once." << endl;
    
  //
  // 3. Which author makes the most total comments?
	
	cout << mostProlificAuthors[9] << " made the most total comments" << endl;

  //
  // 4. For the author with the most comments, what is the min/max UTC time?
    std::map<std::string, size_t>::iterator utcCurrentEntry; 
    utcCurrentEntry = utcInfo.begin();
    size_t highestUtc = 0;
    size_t lowestUtc = utcCurrentEntry->second;
    for (utcCurrentEntry = utcInfo.begin(); utcCurrentEntry != utcInfo.end(); ++utcCurrentEntry) {
      
      if(utcCurrentEntry->first == mostProlificAuthors[9]) {
        if(utcCurrentEntry->second > highestUtc) {
          highestUtc = utcCurrentEntry->second;
        }
        if(utcCurrentEntry->second < lowestUtc) {
          lowestUtc = utcCurrentEntry->second;
        }
      }
    }
    cout << "Max UTC = " << highestUtc << endl;
    cout << "Min UTC = " << lowestUtc << endl;
  //
  // 5. Which author makes the longest comment?   Hint:  body.size()
    std::map<std::string, std::string>::iterator commentIterator;
    size_t longestComment = 0;
    std::string authorLongestComment = "";
    for(commentIterator = commentInfo.begin(); commentIterator != commentInfo.end(); ++commentIterator) {
      if(commentIterator->first.size() > longestComment) {
        longestComment = commentIterator->first.size();
        authorLongestComment = commentIterator->second;
      }
    }
    cout << "Author that posted longest comment: " << authorLongestComment << ", Size: " << longestComment << " characters"<< endl; 
  //
  // 6. Which author types the most? (assume body.size() is how much the author
  // typed).
    std::map<std::string, size_t>::iterator characterCountIterator;
    size_t mostCharacters = 0;
    std::string authorMostCharacters = "";
    for(characterCountIterator = commentCharacterCount.begin(); characterCountIterator != commentCharacterCount.end(); ++ characterCountIterator) {
      if(characterCountIterator->second > mostCharacters) {
        mostCharacters = characterCountIterator->second;
        authorMostCharacters = characterCountIterator->first;
      }
    }
    cout << "Author with most characters: " << authorMostCharacters << ", total characters typed: " << mostCharacters << endl; 
  //
  // 7. Which author comments on the most number of subreddits?

    std::map<std::string, int>::iterator redditCurrentEntry; 
    std::map<std::string, int>::value_compare redditComp = numberRedditsPosted.value_comp();
    std::pair<std::string, int> redditPair;
	std::string mostComments = "";
    int mostSubreddits = numberRedditsPosted.begin()->second;
    for (redditCurrentEntry = numberRedditsPosted.begin(); redditCurrentEntry != numberRedditsPosted.end(); ++redditCurrentEntry) {
      if(redditCurrentEntry->second > mostSubreddits) {
        mostSubreddits = redditCurrentEntry->second;
		//cout << redditCurrentEntry->first << endl;
        redditPair.first = redditCurrentEntry->first;
		mostComments = redditCurrentEntry->first;
      }
    }
	redditPair.second = mostSubreddits;
    std::cout << redditPair.first << " posted on " << redditPair.second << " subreddits. "<< endl;

  //
  // 8. How many authors only comment on 1 subreddit?
	
	std::vector<std::string> singleSubreddit;
	std::map<std::string, int>::iterator singleSubredditIterator; 
    for (singleSubredditIterator = numberRedditsPosted.begin(); singleSubredditIterator != numberRedditsPosted.end(); ++singleSubredditIterator) {
      if(singleSubredditIterator->second == 1) {
        singleSubreddit.push_back(singleSubredditIterator->first);
      }
    }

	cout << singleSubreddit.size() << " authors only comment in one subreddit." << endl;

  //
  // 9. How many subreddits only have 1 author?
		
		std::vector<std::string> singleAuthor;
		std::map<std::string, int>::iterator singleAuthorIterator; 
    	for (singleAuthorIterator = numberAuthors.begin(); singleAuthorIterator != numberAuthors.end(); ++singleAuthorIterator) {
     	 if(singleAuthorIterator->second == 1) {
        	singleAuthor.push_back(singleAuthorIterator->first);
      	}
    	}

	cout << singleAuthor.size() << " subreddits only have one author." << endl;

  //
  // 10. Which subreddit has the most authors?

	std::map<std::string, int>::iterator authorCurrentEntry; 
    std::map<std::string, int>::value_compare authorComp = numberAuthors.value_comp();
    std::pair<std::string, int> authorPair;
	std::string subredditWithMost = "";
    int mostAuthors = numberAuthors.begin()->second;
    for (authorCurrentEntry = numberAuthors.begin(); authorCurrentEntry != numberAuthors.end(); ++authorCurrentEntry) {
      if(authorCurrentEntry->second > mostAuthors) {
        mostAuthors = authorCurrentEntry->second;
		//cout << redditCurrentEntry->first << endl;
        authorPair.first = authorCurrentEntry->first;
		subredditWithMost = authorCurrentEntry->first;
      }
    }
	authorPair.second = mostAuthors;
    std::cout << authorPair.first << " has " << authorPair.second << " authors. "<< endl;



  //////////////////////////////////////////////////////////////////////////////
  // EXTRA CREDIT:  10pts each                                                //
  //        Google is your friend to help tokenize the body of the comments   //
  //////////////////////////////////////////////////////////////////////////////
  
  //
  // 11. Which authors have the shortest and longest average comment length
  
  //
  // 12. Which word is the most frequently used to start a comment?
  //     (Assume words are just characters separated by whitespace)
  
  //
  // 13. For the top 10 commented on subreddits, what is the most used word?
  
  //
  // 14. What is the relative frequency of each character in all comments?
}