
/*********************************************************************************************

                                cfglp : A CFG Language Processor
                                --------------------------------

           About:

           Implemented   by  Tanu  Kanvar (tanu@cse.iitb.ac.in) and Uday
           Khedker    (http://www.cse.iitb.ac.in/~uday)  for the courses
           cs302+cs306: Language  Processors  (theory and  lab)  at  IIT
           Bombay.

           Release  date  Jan  15, 2013.  Copyrights  reserved  by  Uday
           Khedker. This  implemenation  has been made  available purely
           for academic purposes without any warranty of any kind.

           Documentation (functionality, manual, and design) and related
           tools are  available at http://www.cse.iitb.ac.in/~uday/cfglp


***********************************************************************************************/

#include<iostream>
#include<fstream>

using namespace std;

#include"user-options.hh"
#include"error-display.hh"
#include"local-environment.hh"
//#include"procedure.hh"

#include"symbol-table.hh"
#include"ast.hh"


Ast::Ast()
{}

Ast::~Ast()
{}

bool Ast::check_ast(int line)
{
	report_internal_error("Should not reach, Ast : check_ast");
}

Data_Type Ast::get_data_type()
{
	report_internal_error("Should not reach, Ast : get_data_type");
}

void Ast::set_data_type(string *k){
	report_internal_error("Should not reach, Ast : set_data_type");
}

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	report_internal_error("Should not reach, Ast : print_value");
}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	report_internal_error("Should not reach, Ast : get_value_of_evaluation");
}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	report_internal_error("Should not reach, Ast : set_value_of_evaluation");
}

////////////////////////////////////////////////////////////////

Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs)
{
	lhs = temp_lhs;
	rhs = temp_rhs;
}

Assignment_Ast::~Assignment_Ast()
{
	delete lhs;
	delete rhs;
}

Data_Type Assignment_Ast::get_data_type()
{
	return node_data_type;
}

bool Assignment_Ast::check_ast(int line)
{
	if (lhs->get_data_type() == rhs->get_data_type())
	{
		node_data_type = lhs->get_data_type();
		return true;
	}
	////cout<<lhs->get_data_type()<<" "<< rhs->get_data_type()<<endl;
	report_error(" Assignment statement data type not compatible", line);
}

void Assignment_Ast::print_ast(ostream & file_buffer)
{
	file_buffer <<endl<<AST_SPACE << "Asgn:\n";

	file_buffer << AST_NODE_SPACE"LHS (";
	lhs->print_ast(file_buffer);
	file_buffer << ")\n";

	file_buffer << AST_NODE_SPACE << "RHS (";
	rhs->print_ast(file_buffer);
	file_buffer << ")\n";
}



Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = rhs->evaluate(eval_env, file_buffer);

	if (result.is_variable_defined() == false)
		report_error("Variable should be defined to be on asg-rhs", NOLINE);

	lhs->set_value_of_evaluation(eval_env, result);

	// Print the result

	print_ast(file_buffer);

	lhs->print_value(eval_env, file_buffer);

	return result;
}
/////////////////////////////////////////////////////////////////

Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry)
{
	variable_name = name;
	variable_symbol_entry = var_entry;
}

Name_Ast::~Name_Ast()
{}

Data_Type Name_Ast::get_data_type()
{
	return variable_symbol_entry.get_data_type();
}

void Name_Ast::print_ast(ostream & file_buffer)
{
	file_buffer << "Name : " << variable_name;
}

void Name_Ast::set_data_type(string *k)
{
	
	
	if (*k == "INTEGER")
	{
		////cout<<*k<<" yahooint\n";
		variable_symbol_entry.set_data_type(int_data_type);
		////cout<<*k<<" yahoo2\n";
	}
	else if (*k == "FLOAT")
	{
		//	//cout<<*k<<" yahoofloat\n";
		variable_symbol_entry.set_data_type(float_data_type);
	}
	else if (*k == "DOUBLE")
	{
		variable_symbol_entry.set_data_type(float_data_type);
	}

	
}

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result_Value * loc_var_val = eval_env.get_variable_value(variable_name);
	Eval_Result_Value * glob_var_val = interpreter_global_table.get_variable_value(variable_name);

	file_buffer  << AST_SPACE << variable_name << " : ";

	if (!eval_env.is_variable_defined(variable_name) && !interpreter_global_table.is_variable_defined(variable_name))
		file_buffer << "undefined";

	else if (eval_env.is_variable_defined(variable_name) && loc_var_val != NULL)
	{

		if (loc_var_val->get_result_enum() == int_result)
			file_buffer << loc_var_val->get_value().a << "\n";
		else if (loc_var_val->get_result_enum() == float_result)
			file_buffer << loc_var_val->get_value().b << "\n";
		else
			report_internal_error("Result type can only be int and float");
	}

	else
	{
		if (glob_var_val->get_result_enum() == int_result)
		{
			if (glob_var_val == NULL)
				file_buffer << "0\n";
			else
				file_buffer << glob_var_val->get_value().a << "\n";
		}
		else if (glob_var_val->get_result_enum() == float_result)
		{
			if (glob_var_val == NULL)
				file_buffer << "0\n";
			else
				file_buffer << glob_var_val->get_value().b << "\n";
		}
		else
			report_internal_error("Result type can only be int and float");
	}
	file_buffer << "\n";
}


Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	if (eval_env.does_variable_exist(variable_name))
	{
		////cout<<variable_name<<" "<<node_data_type<<endl;
		Eval_Result * result = eval_env.get_variable_value(variable_name);
		////cout<<variable_symbol_entry.get_data_type()<<" -----------"<<endl;
		return *result;
	}

	Eval_Result * result = interpreter_global_table.get_variable_value(variable_name);
	return *result;
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	Eval_Result_Value * i;
	if (variable_symbol_entry.get_data_type()== 1)
	{
		i = new Eval_Result_Value_Int();

		dtype dd;
		dd.a=result.get_value().a;
		dd.b=result.get_value().a;
	 	i->set_value(dd);
	}
	else if(variable_symbol_entry.get_data_type() == 2 || variable_symbol_entry.get_data_type() == 3) {
		i = new Eval_Result_Value_Float();

		dtype dd;
		dd.a=result.get_value().b;
		dd.b=result.get_value().b;
	 	i->set_value(dd);
	}

	if (eval_env.does_variable_exist(variable_name))
		eval_env.put_variable_value(*i, variable_name);
	else
		interpreter_global_table.put_variable_value(*i, variable_name);
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	return get_value_of_evaluation(eval_env);
}

///////////////////////////////////////////////////////////////////////////////

template <class DATA_TYPE>
Number_Ast<DATA_TYPE>::Number_Ast(DATA_TYPE number, Data_Type constant_data_type)
{
	constant = number;
	node_data_type = constant_data_type;
}

template <class DATA_TYPE>
Number_Ast<DATA_TYPE>::~Number_Ast()
{}

template <class DATA_TYPE>
Data_Type Number_Ast<DATA_TYPE>::get_data_type()
{
	return node_data_type;
}

template <class DATA_TYPE>
void Number_Ast<DATA_TYPE>::print_ast(ostream & file_buffer)
{
	//if (node_data)
	file_buffer << "Num : " ;
	file_buffer<<fixed;
	file_buffer<< setprecision(2) <<constant;
}

template <class DATA_TYPE>
void Number_Ast<DATA_TYPE>::set_data_type(string *k)
{
	if (*k == "INTEGER")
	{
		node_data_type=int_data_type;
	}
	else if (*k == "FLOAT")
	{
		node_data_type=float_data_type;
	}
	else if (*k == "DOUBLE")
	{
		node_data_type=float_data_type;
	}
}

template <class DATA_TYPE>
Eval_Result & Number_Ast<DATA_TYPE>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if (node_data_type == int_data_type)
	{
		dtype cons;
		cons.a=constant;
		cons.b=0;
		Eval_Result & result = *new Eval_Result_Value_Int();
		result.set_value(cons);

		return result;
	}
	else 
	{
		dtype cons;
		cons.a=0;
		cons.b=constant;

		Eval_Result & result = *new Eval_Result_Value_Float();
		result.set_value(cons);

		return result;
	}
	
}

///////////////////////////////////////////////////////////////////////////////

Return_Ast::Return_Ast(Ast *b)
{
	//a = new Ast();
	a = b;

}

Return_Ast::~Return_Ast()
{
	delete a;
}

void Return_Ast::print_ast(ostream & file_buffer)
{
	file_buffer << "\n"<<AST_SPACE << "RETURN ";
	if (a == NULL) 
		file_buffer<< "<NOTHING> \n";
	else {
		a->print_ast(file_buffer);
		file_buffer<<endl;
	}
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	
	if (a == NULL) {
		file_buffer << AST_SPACE << "RETURN <NOTHING>\n";
		Eval_Result & result = *new Eval_Result_Value_Int();
		result.set_result_enum(void_result);
		return result;
	}	
	else {
		//file_buffer << AST_SPACE << "RETURN ";

		print_ast(file_buffer);
		Eval_Result & result = a->evaluate(eval_env, file_buffer);
		return result;
	}
}

template class Number_Ast<int>;
//template class Number_Ast<double>;
template class Number_Ast<float>;


/**********************< RELATIONAL >***************************************************/



Relational_Expr_Ast::Relational_Expr_Ast(Ast * temp_lhs, Ast * temp_rhs, string* temp_opr)
{
	lhs = temp_lhs;
	rhs = temp_rhs;	
	ro = *temp_opr;
}

Relational_Expr_Ast::~Relational_Expr_Ast()
{
	delete lhs;
	delete rhs;
}

Data_Type Relational_Expr_Ast::get_data_type()
{
	return node_data_type;
}

void Relational_Expr_Ast::set_data_type(string *k)
{
	if (*k == "INTEGER")
	{
		node_data_type=int_data_type;
	}
	else if (*k == "FLOAT")
	{
		node_data_type=float_data_type;
	}
	else if (*k == "DOUBLE")
	{
		node_data_type=float_data_type;
	}
}

bool Relational_Expr_Ast::check_ast(int line)
{
	////cout<<"ashdfj\n";
	if (lhs == NULL) {
		node_data_type = rhs->get_data_type();
		return true;
	}
	else if (lhs->get_data_type() == rhs->get_data_type())
	{
		node_data_type = lhs->get_data_type();
		return true;
	}
	////cout<<lhs->get_data_type()<<" "<<ro<<" "<< rhs->get_data_type()<<endl;
	report_error("Assignment statement data type not compatible", line);
}

void Relational_Expr_Ast::print_ast(ostream & file_buffer)
{
	////cout<<rhs->get_data_type()<<" data type of rhs\n";
	if (ro == "PLUS" ||ro == "MINUS" || ro == "MULT" ||ro == "DIV" || ro == "UMINUS" ){
		file_buffer << "\n"<<AST_SPACE<< "Arith: "<<ro<<"\n";

	}
	else{
		file_buffer << "\n"<<AST_SPACE << "Condition: "<<ro<<"\n";
	}

	if (lhs== NULL) 
	{
		file_buffer << AST_NODE_SPACE"LHS (";
		rhs->print_ast(file_buffer);
		file_buffer << ")";
	}
	else
	{
		file_buffer << AST_NODE_SPACE"LHS (";
		lhs->print_ast(file_buffer);
		file_buffer << ")\n";
	
		file_buffer << AST_NODE_SPACE << "RHS (";
		rhs->print_ast(file_buffer);
		file_buffer << ")";
	}
}


Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	
	////cout<< "relop evaluate calling "<<endl;
	Eval_Result & result = rhs->evaluate(eval_env, file_buffer);

	if (result.is_variable_defined() == false)
		report_error("Variable should be defined to be on rel-lhs ", NOLINE);
	

	if(node_data_type == 1)
	{
		////cout<<"abc\n";
		Eval_Result & result3 = *new Eval_Result_Value_Int();
		dtype tr;
		tr.a=1;
		tr.b=1;

		dtype fr;
		fr.a=0;
		fr.b=0;

		if(==NULL)
		{

			if (ro == "UMINUS")
			{
				tr.a=0 - result.get_value().a;
				tr.b=0 - result.get_value().a;
				result3.set_value(tr);
				result3.set_result_enum(int_result);
				return result3;
			}
		}
		else
		{

			Eval_Result & result1 = lhs->evaluate(eval_env, file_buffer);

			if (result1.is_variable_defined() == false)
				report_error("Variable should be defined to be on lhs", NOLINE);

			//lhs->set_value_of_evaluation(eval_env, result);
	
			if (ro == "LE"){
				if(result1.get_value().a <= result.get_value().a)
				{
					result3.set_value(tr);
					
				}
				else
				{
					result3.set_value(fr);	
				}
			//	result3.set_result_enum(int_result);
			}
			else if (ro == "LT")
			{
				if(result1.get_value().a < result.get_value().a)
				{
					result3.set_value(tr);
				}
				else
				{
					result3.set_value(fr);	
				}
			//	result3.set_result_enum(int_result);
			}
			else if (ro == "GE")
			{
				if(result1.get_value().a >= result.get_value().a)
				{
					result3.set_value(tr);
				}
				else
				{
					result3.set_value(fr);	
				}
			//	result3.set_result_enum(int_result);
			}
			else if (ro == "GT")
			{
				if(result1.get_value().a > result.get_value().a)
				{
					result3.set_value(tr);
				}
				else
				{
					result3.set_value(fr);	
				}
			//	result3.set_result_enum(int_result);
			}
			else if (ro == "EQ")
			{
				if(result1.get_value().a == result.get_value().a)
				{
					result3.set_value(tr);
				}
				else
				{
					result3.set_value(fr);	
				}
				//result3.set_result_enum(int_result);
			}
			else if (ro == "NE")
			{
				if(result1.get_value().a != result.get_value().a)
				{
					result3.set_value(tr);
				}
				else
				{
					result3.set_value(fr);	
				}
				//result3.set_result_enum(int_result);
			}
			else if (ro == "PLUS")
			{
				//cout<<"+++++++"<<endl;
				tr.a=result1.get_value().a + result.get_value().a;
				tr.b=result1.get_value().a + result.get_value().a;
				result3.set_value(tr);
				
			}
			else if (ro == "MINUS")
			{
				tr.a=result1.get_value().a - result.get_value().a;
				tr.b=result1.get_value().a - result.get_value().a;
				result3.set_value(tr);
			}
			else if (ro == "MULT")
			{
				tr.a=result1.get_value().a * result.get_value().a;
				tr.b=result1.get_value().a * result.get_value().a;
				result3.set_value(tr);
			}
			else if (ro == "DIV")
			{
				if(result.get_value().a==0)
				{
					file_buffer << "error : divide by zero";
					exit (0);
				}
				tr.a=result1.get_value().a / result.get_value().a;
				tr.b=result1.get_value().a / result.get_value().a;
				result3.set_value(tr);
			}
			result3.set_result_enum(int_result);
			return result3;
		}


	}	



/////////////////////////////////// FLOAT  ////////////////////////////////////	
	else if(node_data_type==2 || node_data_type==3)
	{
			
		Eval_Result & result3 = *new Eval_Result_Value_Float();
		dtype tr;
		tr.a=1;
		tr.b=1;

		dtype fr;
		fr.a=0;
		fr.b=0;

		if(lhs==NULL)
		{

			if (ro == "UMINUS")
			{
				tr.a=0 - result.get_value().b;
				tr.b=0 - result.get_value().b;
				result3.set_value(tr);
				result3.set_result_enum(float_result);
				return result3;
				//result3.set_result_enum(int_result);
			}
		}
		else
		{

			Eval_Result & result1 = lhs->evaluate(eval_env, file_buffer);

	if (result1.is_variable_defined() == false)
		report_error("Variable should be defined to be on lhs", NOLINE);

	//lhs->set_value_of_evaluation(eval_env, result);
	
	if (ro == "LE"){
		if(result1.get_value().b <= result.get_value().b)
		{
			result3.set_value(tr);
		}
		else
		{
			result3.set_value(fr);	
		}
		result3.set_result_enum(int_result);
	}
	else if (ro == "LT")
	{
		if(result1.get_value().b < result.get_value().b)
		{
			result3.set_value(tr);
		}
		else
		{
			result3.set_value(fr);	
		}
		result3.set_result_enum(int_result);
	}
	else if (ro == "GE")
	{
		if(result1.get_value().b >= result.get_value().b)
		{
			result3.set_value(tr);
		}
		else
		{
			result3.set_value(fr);	
		}
		result3.set_result_enum(int_result);
	}
	else if (ro == "GT")
	{
		if(result1.get_value().b > result.get_value().b)
		{
			result3.set_value(tr);
		}
		else
		{
			result3.set_value(fr);	
		}
		result3.set_result_enum(int_result);
	}
	else if (ro == "EQ")
	{
		if(result1.get_value().b == result.get_value().b)
		{
			result3.set_value(tr);
		}
		else
		{
			result3.set_value(fr);	
		}
		result3.set_result_enum(int_result);
	}
	else if (ro == "NE")
	{
		if(result1.get_value().b != result.get_value().b)
		{
			result3.set_value(tr);
		}
		else
		{
			result3.set_value(fr);	
		}
		result3.set_result_enum(int_result);
	}
	else if (ro == "PLUS")
	{
		//cout<<"+++++++float"<<endl;
		tr.b=result1.get_value().b + result.get_value().b;
		result3.set_value(tr);
		result3.set_result_enum(float_result);
	}
	else if (ro == "MINUS")
	{
		tr.b=result1.get_value().b - result.get_value().b;
		result3.set_value(tr);
		result3.set_result_enum(float_result);
	}
	else if (ro == "MULT")
	{
		tr.b=result1.get_value().b * result.get_value().b;
		result3.set_value(tr);
		result3.set_result_enum(float_result);
	}
	else if (ro == "DIV")
	{
		if(result.get_value().b==0)
		{
			file_buffer << "error : divide by zero";
			exit (0);
		}
		tr.b=result1.get_value().b / result.get_value().b;
		result3.set_value(tr);
		result3.set_result_enum(float_result);
	}
	//result3.set_result_enum(float_result);
	return result3;
		}


	}
	
}




/**********************************< GOTO >********************************************/


Goto_Ast::Goto_Ast(int temp_bb)
{
	bbno = temp_bb;
}



Goto_Ast::~Goto_Ast()
{}

int Goto_Ast::get_bbno(){
	return bbno;
}

void Goto_Ast::print_ast(ostream & file_buffer){
	file_buffer << AST_SPACE << "Goto statement:\n";

	file_buffer << AST_NODE_SPACE"Successor: "<<bbno<<"\n";
	
}


Eval_Result & Goto_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{

	
	file_buffer <<AST_SPACE<<"Goto statement:\n";
	file_buffer <<AST_NODE_SPACE<< "Successor: " << bbno << "\n";
	file_buffer <<AST_NODE_SPACE<< "GOTO (BB "<<bbno<<")"<< "\n";	

	Eval_Result & result = *new Eval_Result_Value_Goto();
	dtype d;
	d.a=bbno;
	d.b=0;

	result.set_value(d);
	return result;
}

/*********************************< IF-Else >********************************************/

Conditional_Ast::Conditional_Ast(Ast* nr1,Goto_Ast* ng1,Goto_Ast* ng2)
{
	r1=nr1;
	g1=ng1;
	g2=ng2;
}

Conditional_Ast::~Conditional_Ast()
{
	delete r1;
	delete g1;
	delete g2;
}

void Conditional_Ast::print_ast(ostream & file_buffer){
	file_buffer <<"\n"<<AST_SPACE<<"If_Else statement:\n";

	r1->print_ast(file_buffer);
	file_buffer<<"\n"<<AST_NODE_SPACE<<"True Successor: "<<g1->get_bbno()<<"\n";
	file_buffer<<AST_NODE_SPACE<<"False Successor: "<<g2->get_bbno()<<"\n";
}

Eval_Result & Conditional_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{


	Eval_Result & result = r1->evaluate(eval_env, file_buffer);

	if (result.is_variable_defined() == false)
		report_error("Variable should be defined to be on con-rhs", NOLINE);

	
	Eval_Result & result1 = *new Eval_Result_Value_Goto();
	print_ast(file_buffer);
	if(result.get_value().a==1)
	{
		file_buffer<<AST_SPACE<<"Condition True : Goto (BB "<<g1->get_bbno()<<")\n";
		
		dtype dd;
		dd.a=g1->get_bbno();
		dd.b=g1->get_bbno();

		result1.set_value(dd);
		
	}
	else
	{
		file_buffer<<AST_SPACE<<"Condition False : Goto (BB "<<g2->get_bbno()<<")\n";
		dtype dd;
		dd.a=g2->get_bbno();
		dd.b=g2->get_bbno();
		result1.set_value(dd);
		
	}
	return result1;
}


/**********************< FUNCTIONAL >***************************************************/



Functional_Ast::Functional_Ast(string name1, list<Ast*> parameter_list1, Data_Type type)
{
	name = name1;
	//parameter_list  = new list<Ast*>();
	parameter_list =  parameter_list1;	
	node_data_type = type;
}

Functional_Ast::~Functional_Ast()
{
	//delete parameter_list;
	//delete rhs;
}

Data_Type Functional_Ast::get_data_type()
{
	return node_data_type;
}

void Functional_Ast::set_data_type(string *k)
{
	if (*k == "INTEGER")
	{
		node_data_type=int_data_type;
	}
	else if (*k == "FLOAT")
	{
		node_data_type=float_data_type;
	}
	else if (*k == "DOUBLE")
	{
		node_data_type=float_data_type;
	}
}

bool Functional_Ast::check_ast(int line)
{
	
	////cout<<rhs->get_data_type()<<" "<<ro<<" "<< rhs->get_data_type()<<endl;
	//report_error("Assignment statement data type not compatible", line);
}



void Functional_Ast::print_ast(ostream & file_buffer)
{
	////cout<<rhs->get_data_type()<<" data type of rhs\n";
	
		file_buffer << "\n"<<AST_SPACE<< "FN CALL: "<<name<<"(";

		if (!(parameter_list.empty())) {
			list<Ast*>::iterator id;	
			//file_buffer <<"\n"<<AST_NODE_SPACE;
			for ( id = parameter_list.begin(); id != parameter_list.end(); id++) {
				file_buffer <<"\n"<<AST_NODE_SPACE;
				(*id)->print_ast(file_buffer);
				
			}
		}
		file_buffer << ")";
		//file_buffer<< "\n";
}

Eval_Result & Functional_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	
	list<Eval_Result_Value*> *aa = new list<Eval_Result_Value*>();
	list<Ast*>::iterator itr;
	
	for(itr=parameter_list.begin(); itr!=parameter_list.end();itr++)
	{
			Eval_Result & result1= (*itr)->evaluate(eval_env, file_buffer);
			
			Eval_Result_Value * i;
			if (result1.get_result_enum() == int_result)
			{
				i = new Eval_Result_Value_Int();
				dtype dd;
				dd.a=result1.get_value().a;
				dd.b=result1.get_value().a;
				i->set_value(dd);
				aa->push_back(i);
			}

			else if (result1.get_result_enum() == float_result)
			{
				i = new Eval_Result_Value_Float();
			 	dtype dd;
				dd.b=result1.get_value().b;
				dd.a=result1.get_value().b;
				i->set_value(dd);
				aa->push_back(i);
			}
	}





	//Procedure * p = new Procedure(node_data_type, name);	
	Eval_Result & result = program_object.get_proc_map()[name]->evaluate(file_buffer, aa);



	return result;
	
	
}
