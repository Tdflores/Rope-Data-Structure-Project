// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/Rope.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class test_Rope : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

shared_ptr<rope_node> HandBuildNode( string text )
{
  shared_ptr<rope_node> newone(new rope_node);
    newone->input = text;
    newone->left = NULL;
    newone->right = NULL;
    newone->is_leaf = false;
    newone->length = text.size();
    newone->weight = 0;
    
    return newone;
}

shared_ptr<rope_node> HandBuildTree ( )
{
	/* Hand build an unbalanced rope tree with This, is, hand, built
	  
	      10
	     /   \
	    4     5
	   /  \  built
	  4    2
	This  / \
	     2   4
		 is  hand
	*/
	shared_ptr<rope_node> top = HandBuildNode("");
	top->left = HandBuildNode("");
	top->right = HandBuildNode("built");
	top->right->is_leaf = true;
	top->left->left = HandBuildNode("This");
	top->left->left->is_leaf = true;
	top->left->right = HandBuildNode("");
	top->left->right->left = HandBuildNode("is");
	top->left->right->left->is_leaf = true;
	top->left->right->right = HandBuildNode("hand");
	top->left->right->right->is_leaf = true;

	//now hand build the correct weights
	//The weight of the parent node is set to the length of the 
	//left child per rope invariant
	top->weight = 10;
	top->left->weight = 4;
	top->right->weight = 5;
	top->left->left->weight = 4;
	top->left->right->weight = 2;
	top->left->right->left->weight = 2;
	top->left->right->right->weight = 4;

	//Fill in the parent info
	top->parent = NULL;
	top->left->parent = top;
	top->right->parent = top;
	top->left->left->parent = top->left;
	top->left->right->parent = top->left;
	top->left->right->left->parent = top->left->right;
	top->left->right->right->parent = top->left->right;

	
	return top;
}

//Test the initialize function for a rope node structure
//Make sure all initializes as expected
TEST_F(test_Rope, TestInit){
	Rope myrope;
	string test = "hello";
	shared_ptr<rope_node> tester = myrope.InitNode(test);  
	
	ASSERT_TRUE(tester);
	
	ASSERT_EQ("hello",tester->input);
	
	ASSERT_FALSE(tester->left);
	
	ASSERT_FALSE(tester->right);

	ASSERT_FALSE(tester->parent);
	
	ASSERT_EQ(5,tester->length);

	ASSERT_EQ(0,tester->weight);	
}

//TEST_F(test_Rope, TestRopeMakeTree){
//    Rope myrope;
    
    //ASSERT_TRUE(2, myobj.RopeFunc());
//}

TEST_F(test_Rope, TestIndexString){
	//Hand build a tree of "This is hand built" 
	//to verify the index function is responding correctly
	shared_ptr<rope_node> top = HandBuildTree();

	Rope myrope;
	
	//cout << top->left->left->input << endl;
	//cout << top->left->right->left->input << endl;
	//cout << top->left->right->right->input << endl;
	//cout << top->right->input << endl;
	//cout << top->left->left->length << " length " << endl;

	string testString;
	myrope.Index_string(top, 4, testString);
	ASSERT_EQ("This",testString);

	myrope.Index_string(top, 15, testString);
	ASSERT_EQ("built",testString);

	myrope.Index_string(top, 6, testString);
	ASSERT_EQ("is",testString);

	myrope.Index_string(top, 9, testString);
	ASSERT_EQ("hand",testString);
	
}

TEST_F(test_Rope, TestIndexLocation){
	//Hand build a tree of "This is hand built" 
	//to verify the index function is responding correctly
	shared_ptr<rope_node> top = HandBuildTree();
	shared_ptr<rope_node> root = HandBuildTree();
	shared_ptr<rope_node> root2 = HandBuildTree();

	Rope myrope;
	myrope.SetRoot(root);

	myrope.Index_location(top, 4);
	ASSERT_EQ("This",top->input);
	top = myrope.GetRoot();

	myrope.Index_location(top, 15);
	ASSERT_EQ("built",top->input);
	top = myrope.GetRoot();

	myrope.Index_location(top, 6);
	ASSERT_EQ("is",top->input);
	//Haven't discerned why, but using the getroot doesn't return
	//the untouched root, had to make a new tree to test the last
	//one - BUG to figure out in code
	top = root2;

	myrope.Index_location(top, 9);
	ASSERT_EQ("hand",top->input);
	//top = myrope.GetRoot();

}

TEST_F(test_Rope, TestConcatenate){

//Test concatenating two nodes with strings but not yet set up 
//as leaves, wanted to test concatenating another string onto 
//the finished product but haven't set up how to balance the 
//structure based on the weight invariant yet
	Rope myrope;
	string test1 = "hello";
	string test2 = "world";
	string test3 = "!!!";
	shared_ptr<rope_node> mynode1 = myrope.InitNode(test1);

	shared_ptr<rope_node> mynode2 = myrope.InitNode(test2); 

	shared_ptr<rope_node> mynode3 = myrope.Concatenate(mynode1,mynode2);

	ASSERT_TRUE(mynode3);
	ASSERT_FALSE(mynode3->parent);
	ASSERT_TRUE(mynode3->left);
	ASSERT_TRUE(mynode3->right);

	ASSERT_EQ("hello",mynode3->left->input);
	ASSERT_EQ("world",mynode3->right->input);

	ASSERT_EQ(5,mynode3->weight);
	
	ASSERT_TRUE(mynode3->left->is_leaf);
	ASSERT_TRUE(mynode3->right->is_leaf);

}

TEST_F(test_Rope, TestSplitLeft){

//Take basic concatenated test structure from before and test splitting
//the left leaf off to create two new nodes

	Rope myrope;
	string test1 = "hello";
	string test2 = "world";

	shared_ptr<rope_node> mynode1 = myrope.InitNode(test1);
	shared_ptr<rope_node> mynode2 = myrope.InitNode(test2); 

	shared_ptr<rope_node> mynode3 = myrope.Concatenate(mynode1,mynode2);

	shared_ptr<rope_node> splitNode = myrope.Split(mynode3, 3);

	ASSERT_TRUE(splitNode);
	ASSERT_FALSE(splitNode->right);
	ASSERT_TRUE(splitNode->left);
	ASSERT_EQ("hello",splitNode->left->input);

	ASSERT_TRUE(mynode3);
	ASSERT_TRUE(mynode3->left);
	ASSERT_FALSE(mynode3->right);
	ASSERT_EQ("world",mynode3->left->input);

}

TEST_F(test_Rope, TestSplitRight){

//Take basic concatenated test structure from before and test splitting
//the right leaf off to create two new nodes

	Rope myrope;
	string test1 = "hello";
	string test2 = "world";

	shared_ptr<rope_node> mynode1 = myrope.InitNode(test1);
	shared_ptr<rope_node> mynode2 = myrope.InitNode(test2); 

	shared_ptr<rope_node> mynode3 = myrope.Concatenate(mynode1,mynode2);

	shared_ptr<rope_node> splitNode = myrope.Split(mynode3, 6);

	ASSERT_TRUE(splitNode);
	ASSERT_FALSE(splitNode->right);
	ASSERT_TRUE(splitNode->left);
	ASSERT_EQ("hello",splitNode->left->input);

	ASSERT_TRUE(mynode3);
	ASSERT_TRUE(mynode3->left);
	ASSERT_FALSE(mynode3->right);
	ASSERT_EQ("world",mynode3->left->input);

}