
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

#ifndef PROGRAM_HH
#define PROGRAM_HH

#include<string>
#include<map>
#include<list>
#include"procedure.hh"

#define GLOB_SPACE "   "

using namespace std;

class Procedure;
class Program;

extern Program program_object;

class Program
{
	Symbol_Table global_symbol_table;
	map<string, Procedure *> procedure_map;

public:
	Program();
	~Program();
	void delete_all();

	void set_procedure_map(Procedure & proc);
	void set_global_table(Symbol_Table & new_global_table);
	//void update_global_table(map<string, Procedure *> procedure_map);
	void create_procedure_map(map<string, Procedure *> new_procedure_map);
	Symbol_Table_Entry & get_symbol_table_entry(string variable);
	map<string, Procedure *> get_proc_map();
	void print_ast();

	Procedure * get_main_procedure(ostream & file_buffer);

	Eval_Result & evaluate();

	bool variable_in_symbol_list_check(string variable);
	void variable_in_proc_map_check(string symbol, int line);
	
	bool proc_in_proc_map_check(string s);
};

#endif
