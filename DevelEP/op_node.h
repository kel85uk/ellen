#pragma once
#ifndef OP_NODE_H
#define OP_NODE_H
//#include "stdafx.h"
//#include <vector>
using namespace std;
//#include <boost/ptr_container/ptr_vector.hpp>
//#include <boost/utility.hpp>
//enum {NUM,OP,SYM};

class node{
public:
	char type;
	bool on;
	int arity;
	float value;
	float* valpt;
	string varname;
	int c; // complexity
	bool intron; // behavioral intron declaration (used in getComplexity())
	bool op_returns_bool; // whether or not node returns a boolean value
	bool op_takes_bool;  // whether or not the node takes a boolean as its first input
	node() {type=0; on=1; arity=0; intron = 0;op_takes_bool=0;op_returns_bool=0;}
	//node(int set) {type=set;on=1;}
	//operator with specified arity
	node(char stype,int sarity){type=stype; arity=sarity; on=1; setComplexity(); intron = 0;op_takes_bool=0;op_returns_bool=0;}
	//operator with arity lookup
	node(char stype)
	{
		type=stype;
		if (type=='s' || type=='c' || type=='e' || type=='l' || type=='q'){
			arity = 1;
			op_returns_bool=0;
			op_takes_bool=0;
		}
		else if (type=='<' || type=='>' || type=='{' || type=='}'){
			arity=2;
			op_takes_bool=0;
			op_returns_bool=1;
		}
		else if (type=='i'){
			arity=2;
			op_takes_bool=1;
			op_returns_bool=0;
		}
		else if (type=='t'){
			arity=3;
			op_takes_bool=1;
			op_returns_bool=0;
		}
		else
			arity = 2;

		on=1;

		// assign complexity
		setComplexity();
		intron = 0;
	}
	//number
	node(float svalue){type='n'; value=svalue; on=1; arity=0; c=1;intron = 0;op_takes_bool=0;op_returns_bool=0;}
	//variable
	node(string& vname){type='v';varname=vname;on=1;arity=0; c=1;intron = 0;op_takes_bool=0;op_returns_bool=0;}
	//set pointer for variables
	void setpt(float* set)
	{
		if (set==NULL)
			cout<<"bad set";
		valpt=set;
	}
	~node() {}
private:
	void setComplexity()
	{
		// assign complexity
		if (type=='^' || type=='i' || type=='t') 
			c = 5;
		else if (type=='e' || type=='l') 
			c = 4; 
		else if (type=='s' || type=='c' ) 
			c = 3;
		else if (type=='/' || type=='q' || type=='<' || type=='>' || type=='{' || type=='}' ) 
			c = 2;
		else 
			c = 1;
	}
	//void eval(vector<float> & float_stack)=0;
	/*node* clone() const
	{
		return do_clone();
	}*/
//private:
	/*virtual node* do_clone() const
	{
		return new node(*this); 
	}*/
};

//inline node* new_clone(const node& a)
//{
//	return a.clone();
//}

//class n_num : public node{
//public:
//	float value;
//	n_num(){on=1;arity=0;}
//	n_num(float set) {type='n'; value=set; on=1; arity=0;}
//	~n_num(){}
//	virtual void eval(vector<float> & float_stack)	
//	{
//		//if (on)
//			float_stack.push_back(value);
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_num(*this); 
////	}
//};
//
//class n_sym : public node{
//public: 
//	float* valpt;
//	string varname;
//	n_sym(){on=1; arity=0;};
//	n_sym(string& vname)
//	{
//		type='v';
//		varname=vname;
//		on=1;
//	}
//	~n_sym(){}
//	void setpt(float* set)
//	{
//		if (set==NULL)
//			cout<<"bad set";
//
//		valpt=set;
//	}
//	virtual void eval(vector<float> & float_stack)
//	{
//		if (valpt==NULL)
//			cout<<"problem";
//		else
//			float_stack.push_back(*valpt);
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_sym(*this); 
////	}
//};
//
//class n_add: public node{
//public:
//	n_add(){type='+';arity=2;on=1;}
//	~n_add(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=2){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				float n2 = float_stack.back(); float_stack.pop_back();
//
//				float_stack.push_back(n2+n1);
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_add(*this); 
////	}
//};
//
//class n_sub: public node{
//public:
//	n_sub(){type='-';arity=2;on=1;}
//	~n_sub(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=2){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				float n2 = float_stack.back(); float_stack.pop_back();
//
//				float_stack.push_back(n2-n1);
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_sub(*this); 
////	}
//};
//class n_mul: public node{
//public:
//	n_mul(){type='*';arity=2;on=1;}
//	~n_mul(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=2){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				float n2 = float_stack.back(); float_stack.pop_back();
//
//				float_stack.push_back(n2*n1);
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_mul(*this); 
////	}
//};
//class n_div: public node{
//public:
//	n_div(){type='/';on=1;arity=2;}
//	~n_div(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=2){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				float n2 = float_stack.back(); float_stack.pop_back();
//				if(abs(n1)<0.0001)
//					float_stack.push_back(0);
//				else
//					float_stack.push_back(n2/n1);
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_div(*this); 
////	}
//};
//
//class n_sin: public node{
//public:
//	n_sin(){type='s';arity=1;on=1;}
//	~n_sin(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=1){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				float_stack.push_back(sin(n1));
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_sin(*this); 
////	}
//
//};
//
//class n_cos: public node{
//public:
//	n_cos(){type='c';arity=1;on=1;}
//	~n_cos(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=1){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				float_stack.push_back(cos(n1));
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_cos(*this); 
////	}
//};
//
//class n_exp: public node{
//public:
//	n_exp(){type='e';arity=1;on=1;}
//	~n_exp(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=1){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				float_stack.push_back(exp(n1));
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_exp(*this); 
////	}
//};
//
//class n_log: public node{
//public:
//	n_log(){type='l';arity=1;on=1;}
//	~n_log(){}
//	virtual void eval(vector<float> & float_stack)
//	{
//		//if (on){
//			if(float_stack.size()>=1){
//				float n1 = float_stack.back(); float_stack.pop_back();
//				if (abs(n1)<0.0001)
//					float_stack.push_back(0);
//				else
//					float_stack.push_back(log(n1));
//			}
//		//}
//	}
////private:
////	virtual node* do_clone() const
////	{
////		return new n_log(*this); 
////	}
//};

#endif