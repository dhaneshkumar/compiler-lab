
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
#include<typeinfo>

using namespace std;

#include"common-classes.hh"
#include"error-display.hh"
#include"user-options.hh"
#include"local-environment.hh"
#include"icode.hh"
#include"reg-alloc.hh"
#include"symbol-table.hh"
#include"ast.hh"
#include"basic-block.hh"
#include"procedure.hh"
#include"program.hh"

Ast::Ast()
{}

Ast::~Ast()
{}

bool Ast::check_ast()
{
	stringstream msg;
	msg << "No check_ast() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Data_Type Ast::get_data_type()
{
	stringstream msg;
	msg << "No get_data_type() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Symbol_Table_Entry & Ast::get_symbol_entry()
{
	stringstream msg;
	msg << "No get_symbol_entry() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	stringstream msg;
	msg << "No print_value() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	stringstream msg;
	msg << "No get_value_of_evaluation() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	stringstream msg;
	msg << "No set_value_of_evaluation() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register)
{
	stringstream msg;
	msg << "No create_store_stmt() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

////////////////////////////////////////////////////////////////

Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line)
{
	lhs = temp_lhs;
	rhs = temp_rhs;

	ast_num_child = binary_arity;
	node_data_type = void_data_type;

	lineno = line;
}

Assignment_Ast::~Assignment_Ast()
{
	delete lhs;
	delete rhs;
}

bool Assignment_Ast::check_ast()
{
	CHECK_INVARIANT((rhs != NULL), "Rhs of Assignment_Ast cannot be null");
	CHECK_INVARIANT((lhs != NULL), "Lhs of Assignment_Ast cannot be null");

	if (lhs->get_data_type() == rhs->get_data_type())
	{
		node_data_type = lhs->get_data_type();
		return true;
	}

	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, 
		"Assignment statement data type not compatible");
}

void Assignment_Ast::print(ostream & file_buffer)
{
	file_buffer << "\n" << AST_SPACE << "Asgn:";

	file_buffer << "\n" << AST_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")";

	file_buffer << "\n" << AST_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}

Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	CHECK_INVARIANT((rhs != NULL), "Rhs of Assignment_Ast cannot be null");
	Eval_Result & result = rhs->evaluate(eval_env, file_buffer);

	CHECK_INPUT_AND_ABORT(result.is_variable_defined(), "Variable should be defined to be on rhs of Assignment_Ast", lineno);

	CHECK_INVARIANT((lhs != NULL), "Lhs of Assignment_Ast cannot be null");

	lhs->set_value_of_evaluation(eval_env, result);

	// Print the result

	print(file_buffer);

	lhs->print_value(eval_env, file_buffer);

	return result;
}

Code_For_Ast & Assignment_Ast::compile()
{
	/* 
		An assignment x = y where y is a variable is 
		compiled as a combination of load and store statements:
		(load) R <- y 
		(store) x <- R
		If y is a constant, the statement is compiled as:
		(imm_Load) R <- y 
		(store) x <- R
		where imm_Load denotes the load immediate operation.
	*/

	CHECK_INVARIANT((lhs != NULL), "Lhs cannot be null");
	CHECK_INVARIANT((rhs != NULL), "Rhs cannot be null");

	Code_For_Ast & load_stmt = rhs->compile();

	Register_Descriptor * load_register = load_stmt.get_reg();

	Code_For_Ast store_stmt = lhs->create_store_stmt(load_register);


	// Store the statement in ic_list

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;

	if (load_stmt.get_icode_list().empty() == false)
		ic_list = load_stmt.get_icode_list();

	if (store_stmt.get_icode_list().empty() == false)
		ic_list.splice(ic_list.end(), store_stmt.get_icode_list());

	Code_For_Ast * assign_stmt;
	if (ic_list.empty() == false)
		assign_stmt = new Code_For_Ast(ic_list, load_register);

	load_register->reset_use_for_expr_result();

	return *assign_stmt;
}


Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	CHECK_INVARIANT((lhs != NULL), "Lhs cannot be null");
	CHECK_INVARIANT((rhs != NULL), "Rhs cannot be null");

	lra.optimize_lra(mc_2m, lhs, rhs);
	Code_For_Ast load_stmt = rhs->compile_and_optimize_ast(lra);

	Register_Descriptor * result_register = load_stmt.get_reg();

	Code_For_Ast store_stmt = lhs->create_store_stmt(result_register);

	list<Icode_Stmt *> ic_list;

	if (load_stmt.get_icode_list().empty() == false)
		ic_list = load_stmt.get_icode_list();

	if (store_stmt.get_icode_list().empty() == false)
		ic_list.splice(ic_list.end(), store_stmt.get_icode_list());

	Code_For_Ast * assign_stmt;
	if (ic_list.empty() == false)
		assign_stmt = new Code_For_Ast(ic_list, result_register);

	return *assign_stmt;
}

/////////////////////////////////////////////////////////////////

Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line)
{
	variable_symbol_entry = &var_entry;

	CHECK_INVARIANT((variable_symbol_entry->get_variable_name() == name),
		"Variable's symbol entry is not matching its name");

	ast_num_child = zero_arity;
	node_data_type = variable_symbol_entry->get_data_type();
	lineno = line;
}

Name_Ast::~Name_Ast()
{}

Data_Type Name_Ast::get_data_type()
{
	return variable_symbol_entry->get_data_type();
}

Symbol_Table_Entry & Name_Ast::get_symbol_entry()
{
	return *variable_symbol_entry;
}

void Name_Ast::print(ostream & file_buffer)
{
	file_buffer << "Name : " << variable_symbol_entry->get_variable_name();
}

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	string variable_name = variable_symbol_entry->get_variable_name();

	Eval_Result * loc_var_val = eval_env.get_variable_value(variable_name);
	Eval_Result * glob_var_val = interpreter_global_table.get_variable_value(variable_name);

	file_buffer << "\n" << AST_SPACE << variable_name << " : ";

	if (!eval_env.is_variable_defined(variable_name) && !interpreter_global_table.is_variable_defined(variable_name))
		file_buffer << "undefined";

	else if (eval_env.is_variable_defined(variable_name) && loc_var_val != NULL)
	{
		CHECK_INVARIANT(loc_var_val->get_result_enum() == int_result, "Result type can only be int");
		file_buffer << loc_var_val->get_int_value() << "\n";
	}

	else
	{
		CHECK_INVARIANT(glob_var_val->get_result_enum() == int_result, 
			"Result type can only be int and float");

		if (glob_var_val == NULL)
			file_buffer << "0\n";
		else
			file_buffer << glob_var_val->get_int_value() << "\n";
	}
	file_buffer << "\n";
}

Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	string variable_name = variable_symbol_entry->get_variable_name();

	if (eval_env.does_variable_exist(variable_name))
	{
		CHECK_INPUT_AND_ABORT((eval_env.is_variable_defined(variable_name) == true), 
					"Variable should be defined before its use", lineno);

		Eval_Result * result = eval_env.get_variable_value(variable_name);
		return *result;
	}

	CHECK_INPUT_AND_ABORT((interpreter_global_table.is_variable_defined(variable_name) == true), 
				"Variable should be defined before its use", lineno);

	Eval_Result * result = interpreter_global_table.get_variable_value(variable_name);
	return *result;
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	Eval_Result * i;
	string variable_name = variable_symbol_entry->get_variable_name();

	if (variable_symbol_entry->get_data_type() == int_data_type)
		i = new Eval_Result_Value_Int();
	else
		CHECK_INPUT_AND_ABORT(CONTROL_SHOULD_NOT_REACH, "Type of a name can be int/float only", lineno);

	if (result.get_result_enum() == int_result)
	 	i->set_value(result.get_int_value());
	else
		CHECK_INPUT_AND_ABORT(CONTROL_SHOULD_NOT_REACH, "Type of a name can be int/float only", lineno);

	if (eval_env.does_variable_exist(variable_name))
		eval_env.put_variable_value(*i, variable_name);
	else
		interpreter_global_table.put_variable_value(*i, variable_name);
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	return get_value_of_evaluation(eval_env);
}

Code_For_Ast & Name_Ast::compile()
{
	Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);
	Register_Descriptor * result_register = machine_dscr_object.get_new_register();
	Ics_Opd * register_opd = new Register_Addr_Opd(result_register);

	Icode_Stmt * load_stmt = new Move_IC_Stmt(load, opd, register_opd);

	list<Icode_Stmt *> ic_list;
	ic_list.push_back(load_stmt);

	Code_For_Ast & load_code = *new Code_For_Ast(ic_list, result_register);

	return load_code;
}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register)
{
	CHECK_INVARIANT((store_register != NULL), "Store register cannot be null");

	Ics_Opd * register_opd = new Register_Addr_Opd(store_register);
	Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);

	Icode_Stmt * store_stmt = new Move_IC_Stmt(store, register_opd, opd);

	if (command_options.is_do_lra_selected() == false)
		variable_symbol_entry->free_register(store_register);

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
	ic_list.push_back(store_stmt);

	Code_For_Ast & name_code = *new Code_For_Ast(ic_list, store_register);

	return name_code;
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;;

	bool load_needed = lra.is_load_needed();

	Register_Descriptor * result_register = lra.get_register();
	CHECK_INVARIANT((result_register != NULL), "Register cannot be null");
	Ics_Opd * register_opd = new Register_Addr_Opd(result_register);

	Icode_Stmt * load_stmt = NULL;
	if (load_needed)
	{
		Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);

		load_stmt = new Move_IC_Stmt(load, opd, register_opd);
			
		ic_list.push_back(load_stmt);
	}

	Code_For_Ast & load_code = *new Code_For_Ast(ic_list, result_register);

	return load_code;
}

///////////////////////////////////////////////////////////////////////////////

template <class DATA_TYPE>
Number_Ast<DATA_TYPE>::Number_Ast(DATA_TYPE number, Data_Type constant_data_type, int line)
{
	constant = number;
	node_data_type = constant_data_type;

	ast_num_child = zero_arity;

	lineno = line;
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
void Number_Ast<DATA_TYPE>::print(ostream & file_buffer)
{
	file_buffer << std::fixed;
	file_buffer << std::setprecision(2);

	file_buffer << "Num : " << constant;
}

template <class DATA_TYPE>
Eval_Result & Number_Ast<DATA_TYPE>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if (node_data_type == int_data_type)
	{
		Eval_Result & result = *new Eval_Result_Value_Int();
		result.set_value(constant);

		return result;
	}
}

template <class DATA_TYPE>
Code_For_Ast & Number_Ast<DATA_TYPE>::compile()
{
	Register_Descriptor * result_register = machine_dscr_object.get_new_register();
	CHECK_INVARIANT((result_register != NULL), "Result register cannot be null");
	Ics_Opd * load_register = new Register_Addr_Opd(result_register);
	Ics_Opd * opd = new Const_Opd<int>(constant);

	Icode_Stmt * load_stmt = new Move_IC_Stmt(imm_load, opd, load_register);

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
	ic_list.push_back(load_stmt);

	Code_For_Ast & num_code = *new Code_For_Ast(ic_list, result_register);

	return num_code;
}

template <class DATA_TYPE>
Code_For_Ast & Number_Ast<DATA_TYPE>::compile_and_optimize_ast(Lra_Outcome & lra)
{
	CHECK_INVARIANT((lra.get_register() != NULL), "Register assigned through optimize_lra cannot be null");
	Ics_Opd * load_register = new Register_Addr_Opd(lra.get_register());
	Ics_Opd * opd = new Const_Opd<int>(constant);

	Icode_Stmt * load_stmt = new Move_IC_Stmt(imm_load, opd, load_register);

	list<Icode_Stmt *> ic_list;
	ic_list.push_back(load_stmt);

	Code_For_Ast & num_code = *new Code_For_Ast(ic_list, lra.get_register());

	return num_code;
}

///////////////////////////////////////////////////////////////////////////////

Return_Ast::Return_Ast(int line)
{
	lineno = line;
	node_data_type = void_data_type;
	ast_num_child = zero_arity;
}

Return_Ast::~Return_Ast()
{}

void Return_Ast::print(ostream & file_buffer)
{
	file_buffer << "\n" << AST_SPACE << "Return <NOTHING>\n";
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = *new Eval_Result_Value_Int();
	return result;
}

Code_For_Ast & Return_Ast::compile()
{
	Code_For_Ast & ret_code = *new Code_For_Ast();
	return ret_code;
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	Code_For_Ast & ret_code = *new Code_For_Ast();
	return ret_code;
}

template class Number_Ast<int>;


/**********************< RELATIONAL >***************************************************/



Relational_Expr_Ast::Relational_Expr_Ast(Ast * temp_lhs, Ast * temp_rhs, string* temp_opr, int line)
{
	lhs = temp_lhs;
	rhs = temp_rhs;	
	ro = *temp_opr;
	node_data_type = int_data_type;
	lineno = line;
	ast_num_child = binary_arity;
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

bool Relational_Expr_Ast::check_ast()
{
	/*if (lhs->get_data_type() == rhs->get_data_type())
	{
		node_data_type = lhs->get_data_type();
		return true;
	}*/
	CHECK_INVARIANT((lhs->get_data_type() == rhs->get_data_type()),"Assignment statement data type not compatible")

	node_data_type = lhs->get_data_type();
	return true;
	//report_error("Assignment statement data type not compatible", line);
}

void Relational_Expr_Ast::print(ostream & file_buffer)
{
	file_buffer << "\n"<<AST_SPACE << "Condition: "<<ro<<"\n";

	file_buffer << AST_NODE_SPACE"LHS (";
	lhs->print(file_buffer);
	file_buffer << ")\n";

	file_buffer << AST_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}

Code_For_Ast & Relational_Expr_Ast::compile()
{
	/* 
		An relational expression x op y where y is a variable is 
		compiled as a combination of load and store statements:
		(load) R1 <- y 
		(load) R2 <- x
		op: result <- R2, R1
		If y is a constant, the statement is compiled as:
		(imm_Load) R1 <- y 
		(load) R2 <- x
		op: result <- R2, R1
		where imm_Load denotes the load immediate operation.
	*/

	CHECK_INVARIANT((lhs != NULL), "Lhs cannot be null");
	CHECK_INVARIANT((rhs != NULL), "Rhs cannot be null");

	Code_For_Ast  & load_stmt2 = lhs->compile();
	Register_Descriptor * load_register2 = load_stmt2.get_reg();
	Ics_Opd * lhs_register = new Register_Addr_Opd(load_register2);

	Code_For_Ast & load_stmt1 = rhs->compile();

	Register_Descriptor * load_register1 = load_stmt1.get_reg();

	Ics_Opd * rhs_register = new Register_Addr_Opd(load_register1);

	Register_Descriptor * result_register = machine_dscr_object.get_new_register();
	CHECK_INVARIANT((result_register != NULL), "Result register cannot be null");
	Ics_Opd * load_register = new Register_Addr_Opd(result_register);

	// Store the statement in ic_list

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;

	if (load_stmt1.get_icode_list().empty() == false)
		ic_list = load_stmt2.get_icode_list();

	/*if (load_stmt2.get_icode_list().empty() == false)
		ic_list = load_stmt.get_icode_list();
*/
	if (load_stmt2.get_icode_list().empty() == false)
		ic_list.splice(ic_list.end(), load_stmt1.get_icode_list());

	//cout<<ro<< " hahaha \n";
	if (ro == "LE"){
		Icode_Stmt *a = new Compute_IC_Stmt(set_less_equal, lhs_register, rhs_register, load_register);
		ic_list.push_back(a);
	}
	else if (ro == "LT")
	{
		Icode_Stmt *a = new Compute_IC_Stmt(set_less_than, lhs_register, rhs_register, load_register);	
		ic_list.push_back(a);
	}
	else if (ro == "GE")
	{
		Icode_Stmt *a = new Compute_IC_Stmt(set_grt_equal, lhs_register, rhs_register, load_register);
		ic_list.push_back(a);
	}
	else if (ro == "GT")
	{
		Icode_Stmt *a = new Compute_IC_Stmt(set_grt_than, lhs_register, rhs_register, load_register);
		ic_list.push_back(a);
	}
	else if (ro == "EQ")
	{
		Icode_Stmt *a = new Compute_IC_Stmt(set_equal, lhs_register, rhs_register, load_register);
		ic_list.push_back(a);
	}
	else if (ro == "NE")
	{
		Icode_Stmt *a = new Compute_IC_Stmt(set_not_equal, lhs_register, rhs_register, load_register);
		ic_list.push_back(a);
	}

	
	

	Code_For_Ast * assign_stmt;
	if (ic_list.empty() == false){
		//cout<<"ic_list is empty ;: "<<ro<<endl;
		assign_stmt = new Code_For_Ast(ic_list, result_register);
	}
	load_register1->reset_use_for_expr_result();
	load_register2->reset_use_for_expr_result();
	//result_register->reset_use_for_expr_result();
	return *assign_stmt;
	
}

Code_For_Ast & Relational_Expr_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = rhs->evaluate(eval_env, file_buffer);

	CHECK_INVARIANT((result.is_variable_defined()) , "Variable should be defined to be on rhs");


	Eval_Result & result1 = lhs->evaluate(eval_env, file_buffer);

	CHECK_INVARIANT((result1.is_variable_defined()) ,"Variable should be defined to be on lhs");

	//lhs->set_value_of_evaluation(eval_env, result);
	Eval_Result & result3 = *new Eval_Result_Value_Int();
	if (ro == "LE"){
		if(result1.get_int_value() <= result.get_int_value())
		{
			result3.set_value(1);
		}
		else
		{
			result3.set_value(0);	
		}
	}
	else if (ro == "LT")
	{
		if(result1.get_int_value() < result.get_int_value())
		{
			result3.set_value(1);
		}
		else
		{
			result3.set_value(0);	
		}
	}
	else if (ro == "GE")
	{
		if(result1.get_int_value() >= result.get_int_value())
		{
			result3.set_value(1);
		}
		else
		{
			result3.set_value(0);	
		}
	}
	else if (ro == "GT")
	{
		if(result1.get_int_value() > result.get_int_value())
		{
			result3.set_value(1);
		}
		else
		{
			result3.set_value(0);	
		}
	}
	else if (ro == "EQ")
	{
		if(result1.get_int_value() == result.get_int_value())
		{
			result3.set_value(1);
		}
		else
		{
			result3.set_value(0);	
		}
	}
	else if (ro == "NE")
	{
		if(result1.get_int_value() != result.get_int_value())
		{
			result3.set_value(1);
		}
		else
		{
			result3.set_value(0);	
		}
	}


	// Print the result
	//print_ast(file_buffer);

	//lhs->print_value(eval_env, file_buffer);

	return result3;
}


/**********************************< GOTO >********************************************/


Goto_Ast::Goto_Ast(int temp_bb, int line)
{
	bbno = temp_bb;
	lineno = line;
	ast_num_child = unary_arity;

}



Goto_Ast::~Goto_Ast()
{}

int Goto_Ast::get_bbno(){
	return bbno;
}

void Goto_Ast::print(ostream & file_buffer){
	file_buffer << AST_SPACE << "Goto statement:\n";

	file_buffer << AST_NODE_SPACE"Successor: "<<bbno<<"\n";
	
}


Eval_Result & Goto_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{

	
	file_buffer <<AST_SPACE<<"Goto statement:\n";
	file_buffer <<AST_NODE_SPACE<< "Successor: " << bbno << "\n";
	file_buffer <<AST_NODE_SPACE<< "GOTO (BB "<<bbno<<")"<< "\n";	

	Eval_Result & result = *new Eval_Result_Value_Goto();
	result.set_value(bbno);
	return result;
}

Code_For_Ast & Goto_Ast::compile()
{
	Register_Descriptor * result_register = machine_dscr_object.get_new_register();
	CHECK_INVARIANT((result_register != NULL), "Result register cannot be null");
	Ics_Opd * load_register = new Const_Opd<int>(bbno);

	//Code_For_Ast & ret_code = *new Code_For_Ast(); 
	Icode_Stmt * load_stmt = new Control_Flow_IC_Stmt(jump, load_register);

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
	ic_list.push_back(load_stmt);

	result_register->reset_use_for_expr_result();

	Code_For_Ast & num_code = *new Code_For_Ast(ic_list, result_register);

	return num_code;



	//return ret_code;
}

Code_For_Ast & Goto_Ast::compile_and_optimize_ast(Lra_Outcome & lra){
	
}
/*********************************< IF-Else >********************************************/

Conditional_Ast::Conditional_Ast(Ast* nr1,Goto_Ast* ng1,Goto_Ast* ng2, int line)
{
	r1=nr1;
	g1=ng1;
	g2=ng2;
	ast_num_child = binary_arity;
	line  = lineno;
}

Conditional_Ast::~Conditional_Ast()
{
	delete r1;
	delete g1;
	delete g2;
}

void Conditional_Ast::print(ostream & file_buffer){
	file_buffer <<"\n"<<AST_SPACE<<"If_Else statement:\n";

	r1->print(file_buffer);
	file_buffer<<"\n"<<AST_NODE_SPACE<<"True Successor: "<<g1->get_bbno()<<"\n";
	file_buffer<<AST_NODE_SPACE<<"False Successor: "<<g2->get_bbno()<<"\n";
}

Eval_Result & Conditional_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{


	Eval_Result & result = r1->evaluate(eval_env, file_buffer);

	CHECK_INVARIANT(result.is_variable_defined(), "Variable should be defined to be on rhs");
	

	
	Eval_Result & result1 = *new Eval_Result_Value_Goto();
	print(file_buffer);
	if(result.get_int_value()==1)
	{
		file_buffer<<AST_SPACE<<"Condition True : Goto (BB "<<g1->get_bbno()<<")\n";
		
		result1.set_value(g1->get_bbno());
		
	}
	else
	{
		file_buffer<<AST_SPACE<<"Condition False : Goto (BB "<<g2->get_bbno()<<")\n";
		result1.set_value(g2->get_bbno());
		
	}
	return result1;
}

Code_For_Ast & Conditional_Ast::compile()
{

	//CHECK_INVARIANT(( != NULL), "Lhs cannot be null");
	//Ics_Opd * rhs_register = new Register_Addr_Opd(load_register1);

	/*Register_Descriptor * result_register = machine_dscr_object.get_new_register();
	CHECK_INVARIANT((result_register != NULL), "Result register cannot be null");*/

	CHECK_INVARIANT((r1 != NULL), "condition cannot be null");
	Code_For_Ast & load_stmt1 = r1->compile();
	
	Register_Descriptor * load_register = load_stmt1.get_reg();
	Ics_Opd * rhs_register = new Register_Addr_Opd(load_register);

	Ics_Opd * load_register1 = new Const_Opd<int>(g1->get_bbno());
	Ics_Opd * zero_register = new Register_Addr_Opd(machine_dscr_object.get_zero_register());
	Ics_Opd * load_register2 = new Const_Opd<int>(g2->get_bbno());
	//Code_For_Ast & ret_code = *new Code_For_Ast(); 
	Icode_Stmt * load_stmt = new Control_Flow_IC_Stmt(br_not_equal, rhs_register, zero_register , load_register1);

	Icode_Stmt * jump_stmt = new Control_Flow_IC_Stmt(jump, load_register2);

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;

	if (load_stmt1.get_icode_list().empty() == false)
		ic_list = load_stmt1.get_icode_list();
	ic_list.push_back(load_stmt);
	ic_list.push_back(jump_stmt);



	load_register->reset_use_for_expr_result();
	//_register->reset_use_for_expr_result();

	Code_For_Ast & num_code = *new Code_For_Ast(ic_list, load_register);

	return num_code;


	
}

Code_For_Ast & Conditional_Ast::compile_and_optimize_ast(Lra_Outcome & lra){
	
}
