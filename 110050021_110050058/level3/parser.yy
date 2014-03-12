

/*******************************************************************************************

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


*********************************************************************************************/

%scanner ../scanner.h
%scanner-token-function d_scanner.lex()
%filenames parser
%parsefun-source parser.cc

%union 
{
	int integer_value;
	float float_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	list<Basic_Block *> * basic_block_list;
	Procedure * procedure;
	pair <string, Symbol_Table *> * paired;

};

%token <integer_value> INTEGER_NUMBER
%token <string_value> BB
%token <float_value> FLOAT_NUMBER

%token <string_value> NAME
%token RETURN
%token <string_value> INTEGER

%token <string_value> FLOAT
%token <string_value> DOUBLE
%token <string_value> VOID
%token <string_value> IF
%token <string_value> ELSE
%token <string_value> GOTO
%token <string_value> ASSIGN_OP

%left <string_value>NE EQ
%left <string_value> LT LE  GT GE 
%left <string_value> '+' '-' 
%left <string_value> '*' '/' 

%type <paired> procedure_name
%type <string_value> dataType 
%type <symbol_table> declaration_statement_list
%type <symbol_entry> declaration_statement
%type <basic_block_list> basic_block_list
%type <basic_block> basic_block
//%type <string_value> returnType
%type <ast_list> executable_statement_list
%type <ast_list> assignment_statement_list
%type <ast> assignment_statement
%type <ast> relop_expression
%type <ast> if_else_clause
%type <ast> variable
%type <ast> atomic
%type <ast> constant
%type <ast> typecast_exp
%type <ast_list> relop_list
%type <symbol_entry> parameters
%type <symbol_table> parameter_list



%start program

%%

program:

	declaration_statement_list procedure_declarations_list 
	{
		
		//return_statement_used_flag = false;	
		program_object.set_global_table(*$1);
		///program_object.create_procedure_map(*$2);

		/*if ($1)
			$1->global_list_in_proc_map_check(get_line_number());
*/
		delete $1;


		//program_object.update_global_table(*$2);

	}
	procedure_list
	{

	}
|
	procedure_declarations_list
	{

		////////cout<<"enter in 3"<<endl;
		//return_statement_used_flag = false;	
		//program_object.create_procedure_map(*$1);
		//program_object.update_global_table(*$1);
	}
	 procedure_list
	 {

	 }

;

procedure_declarations_list:
	procedure_declarations
	{
		////cout<<"only one\n";
		/*int line = get_line_number();
		string var_name =current_procedure->name;
		if (program_object.variable_in_symbol_list_check(var_name))
		{
			
			report_error("Variable name cannot be same as procedure name", line);
		}

		$$ = new map<string, Procedure *>();
		$$[current_procedure->name]= current_procedure;
		//string s = $1->get_proc_name();*/
	}
|
	procedure_declarations_list procedure_declarations
	{
		////cout<<"more than one\n";
		/*int line = get_line_number();
		string var_name = current_procedure->name;
		if (program_object.variable_in_symbol_list_check(var_name))
		{
			//line = get_line_number();
			report_error("Variable name cannot be same as procedure name", line);
		}
		
		if ($1 != NULL)
		{
			program_object.variable_in_proc_map_check(current_procedure->name, line);

			$$ = $1;
		}

		else
			$$ = new map<string, Procedure *>();

		$$[current_procedure->name]= current_procedure;
*/
	}
;

procedure_name:
	NAME '(' ')'
	{	 
		//set data type accordingly
		//current_procedure = new Procedure(void_data_type, *$1);

		Symbol_Table *s =  new Symbol_Table();

		pair<string, Symbol_Table *>  &p = *new pair<string, Symbol_Table*>();
		//pair *p = new paired();
		p.first = (*$1);
		
		p.second = s;
		$$ = &p;
		//////cout<<$$->first<<" p.first\n";
	}
|
	NAME '(' parameter_list ')'
	{
		//
		//if  (current_procedure->local_symbol_table == NULL) {
			
		//current_procedure->set_local_list(&s);
		Symbol_Table *s =  new Symbol_Table();
		s= $3;
		pair<string, Symbol_Table *>  &p = *new pair<string, Symbol_Table*>();
		//pair *p = new paired();
		p.first = (*$1);
		//////cout<<p.first<<" p.first1\n";
		p.second = $3;
		$$ = &p;

		
	}
;


procedure_declarations:
	dataType procedure_name ';'
	{
		//current_procedure = new Procedure(, $2->first);
		

		//return_statement_used_flag = true;
		if(*$1 == "FLOAT") {
			current_procedure = new Procedure(float_data_type, $2->first);
		}

		else if (*$1 == "DOUBLE") {
			current_procedure = new Procedure(float_data_type, $2->first);
		}

		else if (*$1 == "INTEGER"){
			current_procedure = new Procedure(int_data_type, $2->first);
		}
		//current_procedure->local_symbol_table.set_local_list($2);
		current_procedure->set_local_list(*($2->second) );
		//todo
		/*//check if already eists in global symnbool table or procediure map
		if(program_object.proc_in_proc_map_check(($2->first))){
			//program_object.set_procedure_map(*current_procedure);
			report_error("function already defined in earlier \n", get_line_number());

		}*/
		///to do -done
		program_object.set_procedure_map(*current_procedure);


		

	}
|
	VOID procedure_name ';'
	{
		//////cout<< "setting new procedure "<<$2->first<<endl;
		current_procedure = new Procedure(void_data_type, $2->first);
		current_procedure->set_local_list(*($2->second) );
		/*if(program_object.proc_in_proc_map_check(($2->first))){
			//program_object.set_procedure_map(*current_procedure);
			report_error("function already defined in earlier \n", get_line_number());

		}*/
		program_object.set_procedure_map(*current_procedure);
	}
;


procedure_list:
	procedure_name
	{	 ////////////cout<<"abcd\n";
	
		
		//check if function has been defined already or not $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		return_statement_used_flag = false;				// No return statement in the current procedure till now

		
		//to do
		////to check if the symbol table returned by procedure name os same as current prcedures
		if(!(program_object.proc_in_proc_map_check(($1->first)))){
			//program_object.set_procedure_map(*current_procedure);
			report_error("function not defined in earlier \n",get_line_number());

		}
		else{
			current_procedure = program_object.get_proc_map()[$1->first];
		}
		////cout<<"local table size2 : "<<current_procedure->local_symbol_table.variable_table.size()<<endl;
		list<Symbol_Table_Entry *>::iterator itr;

		for(itr=current_procedure->local_symbol_table.variable_table.begin(); itr != current_procedure->local_symbol_table.variable_table.end();itr++)
		{
			////cout<<"get variable name  :   "<<(*itr)->get_variable_name()<<endl;
		}
		/*
		if($1->second->getVariable_table() != program_object.get_proc_map()[$1->first]->local_symbol_table.getVariable_table()){
			report_error("function parameters do not match\n",get_line_number());
			//done
		}
*/
		 
	}
	procedure_body
	{	 
		//cout<<" BB --no list"<<endl;
	 
	}
|
	procedure_list procedure_name
	{	 ////////////cout<<"abcd\n";
		
		//program_object.set_global_table(*$1);
		return_statement_used_flag = false;				// No return statement in the current procedure till now
		////to check if the symbol table returned by procedure name os same as current prcedures
		/*if(!(program_object.proc_in_proc_map_check(($2->first)))){
			//program_object.set_procedure_map(*current_procedure);
			report_error("function not defined in earlier \n",get_line_number());

		}*/

		list<Symbol_Table_Entry *>::iterator it;
		/*for(it=$2->second->getVariable_table().begin();it != $2->second->getVariable_table().end();it++ )
		{
			//////cout<<"list1 :  "<<(*it)->get_variable_name()<<endl;
		}
*/		//////cout<<$2->first<<" proc name  "<<endl;
		//////cout<<$2->second->getVariable_table().size()<<"size : $2\n";
		////////cout<<$2->second->get_proc_name()<<"name : $2\n";
		//////cout<<program_object.get_proc_map().size()<<" map size "<<endl;


		/*map<string, Procedure *>::iterator it1;
		for (it1=program_object.get_proc_map().begin()  ; it1 !=program_object.get_proc_map().end(); ++it1){
			//////cout<<it1->first<<" in map \n";
		}*/
		

		//////cout<<program_object.get_proc_map()[$2->first]->get_proc_name()<<" proc name"<<endl;
		//////cout<<program_object.get_proc_map()[$2->first]->local_symbol_table.getVariable_table().size()<<"size : $2\n";

		if(!(program_object.proc_in_proc_map_check(($2->first)))){
			//program_object.set_procedure_map(*current_procedure);
			report_error("function not defined in earlier \n",get_line_number());

		}
		else{
			current_procedure = program_object.get_proc_map()[$2->first];
		}
		////cout<<"local table size2 : "<<current_procedure->local_symbol_table.variable_table.size()<<endl;
		list<Symbol_Table_Entry *>::iterator itr;

		for(itr=current_procedure->local_symbol_table.variable_table.begin(); itr != current_procedure->local_symbol_table.variable_table.end();itr++)
		{
			////cout<<"get variable name  :   "<<(*itr)->get_variable_name()<<endl;
		}
		/*if($2->second->getVariable_table() != program_object.get_proc_map()[$2->first]->local_symbol_table.getVariable_table()){
			report_error("function parameters do not match\n",get_line_number());
			//done
		  
		}*/
			//////cout<<"running ----"<<endl;
	}
	procedure_body
	{	 
		//cout<<" BB --body"<<endl;
	}
;





procedure_body:
	'{' declaration_statement_list
	{


		////cout<<"declarations -----"<<endl;
		////////cout<<"declarations 23333-----abc"<<endl;
		/*if  (current_procedure->local_symbol_table.getVariable_table().empty()) {
			////////cout<<"declarations 23333-----abc"<<endl;
			current_procedure->set_local_list(*$2);
			//delete $2;
		}
		else {

			list<Symbol_Table_Entry *>:: iterator it ;
			for ( it = $2->variable_table.begin(); it != $2->variable_table.end();it++){
				////////cout<<"declarations 23333-----abcd"<<(*it)->get_variable_name()<<endl;
				current_procedure->append_symbol(*it);
				////////cout<<"declarations 23333-----abcd334"<<endl;
			
			}
		}*/
		//delete $2;
		/*
		current_procedure->set_local_list(*$2);
		delete $2;
		*/
		////cout<<"declarations 23333-----"<<endl;
	}
	basic_block_list '}'
	{	

		////cout<<"declarations 23-----"<<endl;
		current_procedure->set_basic_block_list(*$4);
		check_bbno_exist(current_procedure->get_basic_block_list());
		
		delete $4;
		 
	}
|	
	'{' basic_block_list '}'
	{	 
		

		current_procedure->set_basic_block_list(*$2);

		check_bbno_exist(current_procedure->get_basic_block_list());

		delete $2;
		 
	}
;

declaration_statement_list:
	declaration_statement
	{	////////cout<<"asdfa\n"; 
		
		int line = get_line_number();
		

		string var_name = $1->get_variable_name();
		if (current_procedure && current_procedure->get_proc_name() == var_name)
		{
			int line = get_line_number();
			report_error("Variable name cannot be same as procedure name", line);
		}

		if(!current_procedure){
			$$ = new Symbol_Table();
			$$->push_symbol($1);
		}
		else  {
			$$ = &(current_procedure->local_symbol_table);
			$$->push_symbol($1);
		}
		
		////cout<<"local table size : "<<current_procedure->local_symbol_table.variable_table.size();

		/*list<Symbol_Table_Entry *>::iterator itr;

		for(itr=current_procedure->local_symbol_table.variable_table.begin(); itr != current_procedure->local_symbol_table.variable_table.end();itr++)
		{
			////cout<<"get variable name  :   "<<(*itr)->get_variable_name()<<endl;
		}*/

		
		 ////////cout<<"declaration finished\n"; 
	}
|
	declaration_statement_list declaration_statement
	{	 
		// if declaration is local then no need to check in global list
		// if declaration is global then this list is global 

		/*////cout<<"local table size : "<<current_procedure->local_symbol_table.variable_table.size();

		list<Symbol_Table_Entry *>::iterator itr;

		for(itr=current_procedure->local_symbol_table.variable_table.begin(); itr != current_procedure->local_symbol_table.variable_table.end();itr++)
		{
			////cout<<"get variable name  :   "<<(*itr)->get_variable_name()<<endl;
		}*/
		



		int line = get_line_number();
		//program_object.variable_in_proc_map_check($2->get_variable_name(), line);

		string var_name = $2->get_variable_name();

		if (current_procedure && current_procedure->get_proc_name() == var_name)
		{
			int line = get_line_number();
			report_error("Variable name cannot be same as procedure name", line);
		}

		if(!current_procedure){

			if($1==NULL)
			{
				$$=new Symbol_Table();
			}
			else
				$$ = $1;
	
			$$->push_symbol($2);
		}
		else  {
			//$$ = &(current_procedure->local_symbol_table);
			$$=$1;
			$$->push_symbol($2);
		}
			

		//$$->push_symbol($2);


		////cout<<"local table size : "<<current_procedure->local_symbol_table.variable_table.size()<<endl;
		 
	}
;

declaration_statement:
	dataType NAME ';'
	{	 
		////////cout<<"decl-----start"<<endl;
		//////////cout<<*$1<<"----" <<endl;
		////////cout<<*$2<<endl;

		if((*$1) == "FLOAT") {
			$$ = new Symbol_Table_Entry(*$2, float_data_type);
		}

		else if (*$1 == "DOUBLE") {
			$$ = new Symbol_Table_Entry(*$2, float_data_type);
		}

		else if (*$1 == "INTEGER"){
			$$ = new Symbol_Table_Entry(*$2, int_data_type);
		}
		//$$ = new Symbol_Table_Entry(*$2, int_data_type);

		////////cout<<"decl-----start12"<<endl;
		delete $2;
		 ////////cout<<"decl-----start34"<<endl;
	}
;

parameter_list:
	parameters
	{
		$$ = new Symbol_Table();
		$$->push_symbol($1);
		
	}
|
	parameter_list ',' parameters
	{
		if($1 != NULL) {
			$$ = $1;
			$$->push_symbol($3);
		
		}
		else {
			$$ = new Symbol_Table();
			$$->push_symbol($3);
		}


	}
;


parameters:
	dataType NAME 
	{	 
		// update datatype here
		if(*$1 == "FLOAT") {
			$$ = new Symbol_Table_Entry(*$2, float_data_type);
		}

		else if (*$1 == "DOUBLE") {
			$$ = new Symbol_Table_Entry(*$2, float_data_type);
		}

		else if (*$1 == "INTEGER"){
			$$ = new Symbol_Table_Entry(*$2, int_data_type);
		}

		delete $2;
		 
	}

;


basic_block_list:
	basic_block_list basic_block
	{	 
		
		if (!$2)
		{
			int line = get_line_number();
			report_error("Basic block doesn't exist", line);
		}

		bb_strictly_increasing_order_check($$, $2->get_bb_number());


		$$ = $1;
		$$->push_back($2);
		 
	}
|
	basic_block
	{	 
		//cout<<" BB --only"<<endl;
		if (!$1)
		{
			int line = get_line_number();
			report_error("Basic block doesn't exist", line);
		}

		$$ = new list<Basic_Block *>;
		$$->push_back($1);
		//cout<<" BB --only1"<<endl;
		 
	}
	
;

basic_block:
	BB ':' executable_statement_list
	{	
		//cout<<" BB --1"<<endl;
		if ((*$1).substr(1,2) != "bb")
		{
			int line = get_line_number();
			report_error("Not basic block lable", line);
		}

		if (atoi(((*$1).substr(4,((*$1).length()-5))).c_str()) < 2)
		{
			int line = get_line_number();
			report_error("Illegal basic block lable", line);
		}

		if ($3 != NULL)
			$$ = new Basic_Block(atoi(((*$1).substr(4,((*$1).length()-5))).c_str()), *$3);
		else
		{
			list<Ast *> * ast_list = new list<Ast *>;
			$$ = new Basic_Block(atoi(((*$1).substr(4,((*$1).length()-5))).c_str()), *ast_list);
		}

		delete $3;
		delete $1;
		//cout<<" BB --2"<<endl;
	}
;


if_else_clause:
	IF '(' relop_expression ')' GOTO BB ';' ELSE GOTO BB 
	{ 
		Goto_Ast  *ab = new  Goto_Ast(atoi(((*$6).substr(4,((*$6).length()-5))).c_str()));
		Goto_Ast  *ab1 = new  Goto_Ast(atoi(((*$10).substr(4,((*$10).length()-5))).c_str()));

		store_goto( ab->get_bbno());
		store_goto( ab1->get_bbno());
		
		$$ = new Conditional_Ast($3, ab, ab1);
		
	}
;

relop_list :

relop_list ',' relop_expression
	{
		if($1 == NULL)
		{
			$$ = new list <Ast*>();
		}
		else
		{
			$$=$1;
		}

		$$->push_back($3);
	}
|
	relop_expression
	{
		$$ = new list <Ast*>();
		$$->push_back($1);
	}
;

relop_expression : 
	atomic
	{ 
		$$ = $1;
		
	}
|
	
	relop_expression LT relop_expression
	{ 
		$$ = new Relational_Expr_Ast($1, $3, $2);

		int line = get_line_number();
		$$->check_ast(line);

		string k="INTEGER";
		$$->set_data_type(&k);
		
	}
|
	relop_expression LE relop_expression
	{ 
		$$ = new Relational_Expr_Ast($1, $3, $2);

		int line = get_line_number();
		$$->check_ast(line);
		string k="INTEGER";
		$$->set_data_type(&k);
		
	}
|
	relop_expression GT relop_expression
	{ 
		$$ = new Relational_Expr_Ast($1, $3, $2);

		int line = get_line_number();
		$$->check_ast(line);
		string k="INTEGER";
		$$->set_data_type(&k);
		
	}
|
	relop_expression GE relop_expression
	{ 
		$$ = new Relational_Expr_Ast($1, $3, $2);

		int line = get_line_number();
		$$->check_ast(line);
		string k="INTEGER";
		$$->set_data_type(&k);
		
	}
|
	relop_expression EQ relop_expression
	{ 
		$$ = new Relational_Expr_Ast($1, $3, $2);

		int line = get_line_number();
		$$->check_ast(line);
		string k="INTEGER";
		$$->set_data_type(&k);
		
	}
|
	relop_expression NE relop_expression
	{ 
		$$ = new Relational_Expr_Ast($1, $3, $2);

		int line = get_line_number();
		$$->check_ast(line);
		string k="INTEGER";
		$$->set_data_type(&k);
		
	}
|

	relop_expression '+' relop_expression
	{ 
		string k = "PLUS";
		$$ = new Relational_Expr_Ast($1, $3, &k);

		int line = get_line_number();
		$$->check_ast(line);
		
	}
|

	relop_expression '-' relop_expression
	{ 
		string k = "MINUS";
		$$ = new Relational_Expr_Ast($1, $3, &k);

		int line = get_line_number();
		$$->check_ast(line);
		
	}
|

	relop_expression '*' relop_expression
	{ 
		string k  = "MULT";
		$$ = new Relational_Expr_Ast($1, $3, &k);

		int line = get_line_number();
		$$->check_ast(line);
		
	}
|

	relop_expression '/' relop_expression
	{ 	
		string k  = "DIV";
		$$ = new Relational_Expr_Ast($1, $3, &k);

		int line = get_line_number();
		$$->check_ast(line);
		
	}
|
	typecast_exp
	{ 
		$$ = $1;
		
	}
|	
	'-' atomic
	{
		string k = "UMINUS";
		////////////cout<<$2->get_data_type()<<" dfkj\n";
		$$ = new Relational_Expr_Ast(NULL,$2, &k);
		////////////cout<<$2->get_data_type()<<" zbc\n";
		int line = get_line_number();
		$$->check_ast(line);
	}
;


atomic:
	variable
	{
		$$ = $1;
	}
|
	constant
	{
		$$ = $1;
	}
|
	'(' relop_expression ')'
	{
		$$ = $2;
	}
|   
	NAME '(' relop_list ')'
	{

		Ast* fn = new Functional_Ast(*$1, *$3, program_object.get_proc_map()[*$1]->get_return_type());
		$$ = fn;
	}
|
	NAME '(' ')'
	{
		list<Ast*> *l1 = new list<Ast*>();
		Ast* fn = new Functional_Ast(*$1, *l1, program_object.get_proc_map()[*$1]->get_return_type());
		$$ = fn;
	}
;


dataType :
	FLOAT
	{

		$$= $1;	
	}
|
	DOUBLE
	{
		$$= $1;
	}
|
	INTEGER
	{
		////////cout<<"int "<<endl;
		$$= $1;
		////////cout<<*$1<<endl;
	}
;



typecast_exp:
	'(' dataType ')' atomic
	{
		////////////cout<<"type casting :"<<endl;
		$$ = $4;
		$$->set_data_type($2);
		////////////cout<<*($2)<<" Hahahah "<<$$->get_data_type()<<endl;
		
	}
;



executable_statement_list:
	assignment_statement_list
	{	 
		////////cout<<"assignment_statement :"<<endl;
		$$ = $1;
		 
	}
|
	assignment_statement_list NAME '(' relop_list ')' ';' executable_statement_list
	{	 
		if ($1 != NULL){
			$$ = $1;
			}
		else
			$$ = new list<Ast *>; 

		Ast* fn = new Functional_Ast(*$2, *$4, program_object.get_proc_map()[*$2]->get_return_type());
		$$->push_back(fn);

		
	
	 
	
	 	if($7 !=NULL){
	 		list<Ast *>::iterator it;
			for (it = $7->begin(); it != $7->end(); it++){
				$$->push_back(*it);
			}
		}
	 }
|
	
	assignment_statement_list NAME '(' ')' ';' executable_statement_list
	{	

		if ($1 != NULL){
			$$ = $1;
			
		}
		else
			$$ = new list<Ast *>; 

		list<Ast*> *l1 = new list<Ast*>();
		Ast* fn = new Functional_Ast(*$2, *l1, program_object.get_proc_map()[*$2]->get_return_type());
		$$->push_back(fn);
		//cout<< "main pain5"<<endl;
		
		
		 //cout<< "main pain-----------"<<endl;
	
		if($6!=NULL){
			//cout<<$$->size()<<" : size"<<endl;
			list<Ast *>::iterator it;
			for (it = $6->begin(); it != $6->end(); it++){
				$$->push_back(*it);
			}
			

		}
	}
|
	assignment_statement_list RETURN ';'
	{	 

		//cout<<"assignment_statement with void returns "<<endl;
		Ast * ret = new Return_Ast(NULL);

		return_statement_used_flag = true;					// Current procedure has an occurrence of return statement

		if ($1 != NULL)
			$$ = $1;

		else
			$$ = new list<Ast *>;

		$$->push_back(ret);
		 //cout<<"assignment_statement with void returns 89 "<<endl;
	}
|
	assignment_statement_list RETURN relop_expression ';'
	{	 
		//cout<<" BB --23"<<endl;

		Ast * ret = new Return_Ast( $3);

		return_statement_used_flag = true;					// Current procedure has an occurrence of return statement

		if ($1 != NULL)
			$$ = $1;

		else
			$$ = new list<Ast *>;

		$$->push_back(ret);
		 //cout<<" BB --23"<<endl;
	}

| 	
	assignment_statement_list GOTO BB ';'
	{ 
		Ast * ret = new Goto_Ast( atoi(((*$3).substr(4,((*$3).length()-5))).c_str()));
		Goto_Ast * ret1 = new Goto_Ast( atoi(((*$3).substr(4,((*$3).length()-5))).c_str()));

		store_goto( ret1->get_bbno());

		if ($1 != NULL)
			$$ = $1;

		else
			$$ = new list<Ast *>;

		$$->push_back(ret);
		
	}

|
	assignment_statement_list if_else_clause ';'
	{ 
		if ($1 == NULL)
			$$ = new list<Ast *>;

		else
			$$ = $1;

		$$->push_back($2);
		
	}

	
;

assignment_statement_list:
	{	 
		$$ = NULL;
		 
	}

|
	assignment_statement_list assignment_statement
	{	 
		if ($1 == NULL)
			$$ = new list<Ast *>;

		else
			$$ = $1;

		$$->push_back($2);
		 
	}

;

assignment_statement:
	
	variable ASSIGN_OP relop_expression ';'
	{ 
		$$ = new Assignment_Ast($1, $3);
		////////////cout<<$3->get_data_type()<<" abc\n";
		int line = get_line_number();
		$$->check_ast(line);
		
	}
;



variable:
	NAME
	{	 
		Symbol_Table_Entry var_table_entry;


		if (current_procedure->variable_in_symbol_list_check(*$1))
			 var_table_entry = current_procedure->get_symbol_table_entry(*$1);

		else if (program_object.variable_in_symbol_list_check(*$1))
			var_table_entry = program_object.get_symbol_table_entry(*$1);

		else
		{
			////cout<<*$1<<" ---"<<endl;
			int line = get_line_number();
			report_error("Variable has not been declared", line);
		}

		$$ = new Name_Ast(*$1, var_table_entry);

		delete $1;
		 
	}
;

constant:
	INTEGER_NUMBER
	{	 
		$$ = new Number_Ast<int>($1, int_data_type);
		 
	}
	
|
	FLOAT_NUMBER
	{
		$$ = new Number_Ast<float>($1, float_data_type);
	}


;


