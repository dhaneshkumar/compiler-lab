// Generated by Bisonc++ V2.09.03 on Thu, 06 Feb 2014 01:10:53 +0530

// $insert class.ih
#include "parser.ih"

// The FIRST element of SR arrays shown below uses `d_type', defining the
// state's type, and `d_lastIdx' containing the last element's index. If
// d_lastIdx contains the REQ_TOKEN bitflag (see below) then the state needs
// a token: if in this state d_token__ is _UNDETERMINED_, nextToken() will be
// called

// The LAST element of SR arrays uses `d_token' containing the last retrieved
// token to speed up the (linear) seach.  Except for the first element of SR
// arrays, the field `d_action' is used to determine what to do next. If
// positive, it represents the next state (used with SHIFT); if zero, it
// indicates `ACCEPT', if negative, -d_action represents the number of the
// rule to reduce to.

// `lookup()' tries to find d_token__ in the current SR array. If it fails, and
// there is no default reduction UNEXPECTED_TOKEN__ is thrown, which is then
// caught by the error-recovery function.

// The error-recovery function will pop elements off the stack until a state
// having bit flag ERR_ITEM is found. This state has a transition on _error_
// which is applied. In this _error_ state, while the current token is not a
// proper continuation, new tokens are obtained by nextToken(). If such a
// token is found, error recovery is successful and the token is
// handled according to the error state's SR table and parsing continues.
// During error recovery semantic actions are ignored.

// A state flagged with the DEF_RED flag will perform a default
// reduction if no other continuations are available for the current token.

// The ACCEPT STATE never shows a default reduction: when it is reached the
// parser returns ACCEPT(). During the grammar
// analysis phase a default reduction may have been defined, but it is
// removed during the state-definition phase.

// So:
//      s_x[] = 
//      {
//                  [_field_1_]         [_field_2_]
//
// First element:   {state-type,        idx of last element},
// Other elements:  {required token,    action to perform},
//                                      ( < 0: reduce, 
//                                          0: ACCEPT,
//                                        > 0: next state)
// Last element:    {set to d_token__,    action to perform}
//      }

// When the --thread-safe option is specified, all static data are defined as
// const. If --thread-safe is not provided, the state-tables are not defined
// as const, since the lookup() function below will modify them


namespace // anonymous
{
    char const author[] = "Frank B. Brokken (f.b.brokken@rug.nl)";

    enum 
    {
        STACK_EXPANSION = 5     // size to expand the state-stack with when
                                // full
    };

    enum ReservedTokens
    {
        PARSE_ACCEPT     = 0,   // `ACCEPT' TRANSITION
        _UNDETERMINED_   = -2,
        _EOF_            = -1,
        _error_          = 256
    };
    enum StateType       // modify statetype/data.cc when this enum changes
    {
        NORMAL,
        ERR_ITEM,
        REQ_TOKEN,
        ERR_REQ,    // ERR_ITEM | REQ_TOKEN
        DEF_RED,    // state having default reduction
        ERR_DEF,    // ERR_ITEM | DEF_RED
        REQ_DEF,    // REQ_TOKEN | DEF_RED
        ERR_REQ_DEF // ERR_ITEM | REQ_TOKEN | DEF_RED
    };    
    struct PI__     // Production Info
    {
        size_t d_nonTerm; // identification number of this production's
                            // non-terminal 
        size_t d_size;    // number of elements in this production 
    };

    struct SR__     // Shift Reduce info, see its description above
    {
        union
        {
            int _field_1_;      // initializer, allowing initializations 
                                // of the SR s_[] arrays
            int d_type;
            int d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // if negative, the state uses SHIFT
            int d_action;           // may be negative (reduce), 
                                    // postive (shift), or 0 (accept)
            size_t d_errorState;    // used with Error states
        };
    };

    // $insert staticdata
    
// Productions Info Records:
PI__ const s_productionInfo[] = 
{
     {0, 0}, // not used: reduction values are negative
     {282, 4}, // 1: program ->  declaration_statement_list procedure_name #0001 procedure_body
     {285, 0}, // 2: #0001 ->  <empty>
     {282, 3}, // 3: program ->  procedure_name #0002 procedure_body
     {286, 0}, // 4: #0002 ->  <empty>
     {283, 3}, // 5: procedure_name (NAME) ->  NAME '(' ')'
     {284, 5}, // 6: procedure_body ('{') ->  '{' declaration_statement_list #0003 basic_block_list '}'
     {287, 0}, // 7: #0003 ->  <empty>
     {284, 3}, // 8: procedure_body ('{') ->  '{' basic_block_list '}'
     {288, 1}, // 9: declaration_statement_list ->  declaration_statement
     {288, 2}, // 10: declaration_statement_list ->  declaration_statement_list declaration_statement
     {289, 3}, // 11: declaration_statement (INTEGER) ->  INTEGER NAME ';'
     {290, 2}, // 12: basic_block_list ->  basic_block_list basic_block
     {290, 1}, // 13: basic_block_list ->  basic_block
     {291, 3}, // 14: basic_block (BB) ->  BB ':' executable_statement_list
     {292, 3}, // 15: relop_expression (LT) ->  relop_expression LT relop_expression
     {292, 3}, // 16: relop_expression (LE) ->  relop_expression LE relop_expression
     {292, 3}, // 17: relop_expression (GT) ->  relop_expression GT relop_expression
     {292, 3}, // 18: relop_expression (GE) ->  relop_expression GE relop_expression
     {292, 3}, // 19: relop_expression (EQ) ->  relop_expression EQ relop_expression
     {292, 3}, // 20: relop_expression (NE) ->  relop_expression NE relop_expression
     {292, 1}, // 21: relop_expression ->  variable
     {292, 1}, // 22: relop_expression ->  constant
     {293, 1}, // 23: executable_statement_list ->  assignment_statement_list
     {293, 3}, // 24: executable_statement_list (RETURN) ->  assignment_statement_list RETURN ';'
     {293, 4}, // 25: executable_statement_list (GOTO) ->  assignment_statement_list GOTO BB ';'
     {294, 0}, // 26: assignment_statement_list ->  <empty>
     {294, 2}, // 27: assignment_statement_list ->  assignment_statement_list assignment_statement
     {295, 4}, // 28: assignment_statement (ASSIGN_OP) ->  variable ASSIGN_OP variable ';'
     {295, 4}, // 29: assignment_statement (ASSIGN_OP) ->  variable ASSIGN_OP constant ';'
     {295, 4}, // 30: assignment_statement (ASSIGN_OP) ->  variable ASSIGN_OP relop_expression ';'
     {296, 1}, // 31: variable (NAME) ->  NAME
     {297, 1}, // 32: constant (INTEGER_NUMBER) ->  INTEGER_NUMBER
     {298, 1}, // 33: program_$ ->  program
};

// State info and SR__ transitions for each state.


SR__ s_0[] =
{
    { { REQ_TOKEN}, { 7} },                              
    { {       282}, { 1} }, // program                   
    { {       288}, { 2} }, // declaration_statement_list
    { {       283}, { 3} }, // procedure_name            
    { {       289}, { 4} }, // declaration_statement     
    { {       259}, { 5} }, // NAME                      
    { {       261}, { 6} }, // INTEGER                   
    { {         0}, { 0} },                              
};

SR__ s_1[] =
{
    { { REQ_TOKEN}, {            2} }, 
    { {     _EOF_}, { PARSE_ACCEPT} }, 
    { {         0}, {            0} }, 
};

SR__ s_2[] =
{
    { { REQ_TOKEN}, { 5} },                         
    { {       283}, { 7} }, // procedure_name       
    { {       289}, { 8} }, // declaration_statement
    { {       259}, { 5} }, // NAME                 
    { {       261}, { 6} }, // INTEGER              
    { {         0}, { 0} },                         
};

SR__ s_3[] =
{
    { { DEF_RED}, {  2} },         
    { {     286}, {  9} }, // #0002
    { {       0}, { -4} },         
};

SR__ s_4[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -9} }, 
};

SR__ s_5[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        40}, { 10} }, // '('
    { {         0}, {  0} },       
};

SR__ s_6[] =
{
    { { REQ_TOKEN}, {  2} },        
    { {       259}, { 11} }, // NAME
    { {         0}, {  0} },        
};

SR__ s_7[] =
{
    { { DEF_RED}, {  2} },         
    { {     285}, { 12} }, // #0001
    { {       0}, { -2} },         
};

SR__ s_8[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -10} }, 
};

SR__ s_9[] =
{
    { { REQ_TOKEN}, {  3} },                  
    { {       284}, { 13} }, // procedure_body
    { {       123}, { 14} }, // '{'           
    { {         0}, {  0} },                  
};

SR__ s_10[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        41}, { 15} }, // ')'
    { {         0}, {  0} },       
};

SR__ s_11[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        59}, { 16} }, // ';'
    { {         0}, {  0} },       
};

SR__ s_12[] =
{
    { { REQ_TOKEN}, {  3} },                  
    { {       284}, { 17} }, // procedure_body
    { {       123}, { 14} }, // '{'           
    { {         0}, {  0} },                  
};

SR__ s_13[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -3} }, 
};

SR__ s_14[] =
{
    { { REQ_TOKEN}, {  7} },                              
    { {       288}, { 18} }, // declaration_statement_list
    { {       290}, { 19} }, // basic_block_list          
    { {       289}, {  4} }, // declaration_statement     
    { {       291}, { 20} }, // basic_block               
    { {       261}, {  6} }, // INTEGER                   
    { {       258}, { 21} }, // BB                        
    { {         0}, {  0} },                              
};

SR__ s_15[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -5} }, 
};

SR__ s_16[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -11} }, 
};

SR__ s_17[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -1} }, 
};

SR__ s_18[] =
{
    { { REQ_DEF}, {  4} },                         
    { {     287}, { 22} }, // #0003                
    { {     289}, {  8} }, // declaration_statement
    { {     261}, {  6} }, // INTEGER              
    { {       0}, { -7} },                         
};

SR__ s_19[] =
{
    { { REQ_TOKEN}, {  4} },               
    { {       125}, { 23} }, // '}'        
    { {       291}, { 24} }, // basic_block
    { {       258}, { 21} }, // BB         
    { {         0}, {  0} },               
};

SR__ s_20[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -13} }, 
};

SR__ s_21[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        58}, { 25} }, // ':'
    { {         0}, {  0} },       
};

SR__ s_22[] =
{
    { { REQ_TOKEN}, {  4} },                    
    { {       290}, { 26} }, // basic_block_list
    { {       291}, { 20} }, // basic_block     
    { {       258}, { 21} }, // BB              
    { {         0}, {  0} },                    
};

SR__ s_23[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -8} }, 
};

SR__ s_24[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -12} }, 
};

SR__ s_25[] =
{
    { { DEF_RED}, {   3} },                             
    { {     293}, {  27} }, // executable_statement_list
    { {     294}, {  28} }, // assignment_statement_list
    { {       0}, { -26} },                             
};

SR__ s_26[] =
{
    { { REQ_TOKEN}, {  4} },               
    { {       125}, { 29} }, // '}'        
    { {       291}, { 24} }, // basic_block
    { {       258}, { 21} }, // BB         
    { {         0}, {  0} },               
};

SR__ s_27[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -14} }, 
};

SR__ s_28[] =
{
    { { REQ_DEF}, {   6} },                        
    { {     260}, {  30} }, // RETURN              
    { {     264}, {  31} }, // GOTO                
    { {     295}, {  32} }, // assignment_statement
    { {     296}, {  33} }, // variable            
    { {     259}, {  34} }, // NAME                
    { {       0}, { -23} },                        
};

SR__ s_29[] =
{
    { { DEF_RED}, {  1} }, 
    { {       0}, { -6} }, 
};

SR__ s_30[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        59}, { 35} }, // ';'
    { {         0}, {  0} },       
};

SR__ s_31[] =
{
    { { REQ_TOKEN}, {  2} },      
    { {       258}, { 36} }, // BB
    { {         0}, {  0} },      
};

SR__ s_32[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -27} }, 
};

SR__ s_33[] =
{
    { { REQ_TOKEN}, {  2} },             
    { {       265}, { 37} }, // ASSIGN_OP
    { {         0}, {  0} },             
};

SR__ s_34[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -31} }, 
};

SR__ s_35[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -24} }, 
};

SR__ s_36[] =
{
    { { REQ_TOKEN}, {  2} },       
    { {        59}, { 38} }, // ';'
    { {         0}, {  0} },       
};

SR__ s_37[] =
{
    { { REQ_TOKEN}, {  6} },                    
    { {       296}, { 39} }, // variable        
    { {       297}, { 40} }, // constant        
    { {       292}, { 41} }, // relop_expression
    { {       259}, { 34} }, // NAME            
    { {       257}, { 42} }, // INTEGER_NUMBER  
    { {         0}, {  0} },                    
};

SR__ s_38[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -25} }, 
};

SR__ s_39[] =
{
    { { REQ_DEF}, {   1} }, 
    { {       0}, { -21} }, 
};

SR__ s_40[] =
{
    { { REQ_DEF}, {   1} }, 
    { {       0}, { -22} }, 
};

SR__ s_41[] =
{
    { { REQ_TOKEN}, {  8} },       
    { {        59}, { 45} }, // ';'
    { {       268}, { 46} }, // LT 
    { {       269}, { 47} }, // LE 
    { {       270}, { 48} }, // GT 
    { {       271}, { 49} }, // GE 
    { {       267}, { 50} }, // EQ 
    { {       266}, { 51} }, // NE 
    { {         0}, {  0} },       
};

SR__ s_42[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -32} }, 
};

SR__ s_43[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -28} }, 
};

SR__ s_44[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -29} }, 
};

SR__ s_45[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -30} }, 
};

SR__ s_46[] =
{
    { { REQ_TOKEN}, {  6} },                    
    { {       292}, { 52} }, // relop_expression
    { {       296}, { 53} }, // variable        
    { {       297}, { 54} }, // constant        
    { {       259}, { 34} }, // NAME            
    { {       257}, { 42} }, // INTEGER_NUMBER  
    { {         0}, {  0} },                    
};

SR__ s_47[] =
{
    { { REQ_TOKEN}, {  6} },                    
    { {       292}, { 55} }, // relop_expression
    { {       296}, { 53} }, // variable        
    { {       297}, { 54} }, // constant        
    { {       259}, { 34} }, // NAME            
    { {       257}, { 42} }, // INTEGER_NUMBER  
    { {         0}, {  0} },                    
};

SR__ s_48[] =
{
    { { REQ_TOKEN}, {  6} },                    
    { {       292}, { 56} }, // relop_expression
    { {       296}, { 53} }, // variable        
    { {       297}, { 54} }, // constant        
    { {       259}, { 34} }, // NAME            
    { {       257}, { 42} }, // INTEGER_NUMBER  
    { {         0}, {  0} },                    
};

SR__ s_49[] =
{
    { { REQ_TOKEN}, {  6} },                    
    { {       292}, { 57} }, // relop_expression
    { {       296}, { 53} }, // variable        
    { {       297}, { 54} }, // constant        
    { {       259}, { 34} }, // NAME            
    { {       257}, { 42} }, // INTEGER_NUMBER  
    { {         0}, {  0} },                    
};

SR__ s_50[] =
{
    { { REQ_TOKEN}, {  6} },                    
    { {       292}, { 58} }, // relop_expression
    { {       296}, { 53} }, // variable        
    { {       297}, { 54} }, // constant        
    { {       259}, { 34} }, // NAME            
    { {       257}, { 42} }, // INTEGER_NUMBER  
    { {         0}, {  0} },                    
};

SR__ s_51[] =
{
    { { REQ_TOKEN}, {  6} },                    
    { {       292}, { 59} }, // relop_expression
    { {       296}, { 53} }, // variable        
    { {       297}, { 54} }, // constant        
    { {       259}, { 34} }, // NAME            
    { {       257}, { 42} }, // INTEGER_NUMBER  
    { {         0}, {  0} },                    
};

SR__ s_52[] =
{
    { { REQ_DEF}, {   1} }, 
    { {       0}, { -15} }, 
};

SR__ s_53[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -21} }, 
};

SR__ s_54[] =
{
    { { DEF_RED}, {   1} }, 
    { {       0}, { -22} }, 
};

SR__ s_55[] =
{
    { { REQ_DEF}, {   1} }, 
    { {       0}, { -16} }, 
};

SR__ s_56[] =
{
    { { REQ_DEF}, {   1} }, 
    { {       0}, { -17} }, 
};

SR__ s_57[] =
{
    { { REQ_DEF}, {   1} }, 
    { {       0}, { -18} }, 
};

SR__ s_58[] =
{
    { { REQ_DEF}, {   5} },      
    { {     268}, {  46} }, // LT
    { {     269}, {  47} }, // LE
    { {     270}, {  48} }, // GT
    { {     271}, {  49} }, // GE
    { {       0}, { -19} },      
};

SR__ s_59[] =
{
    { { REQ_DEF}, {   5} },      
    { {     268}, {  46} }, // LT
    { {     269}, {  47} }, // LE
    { {     270}, {  48} }, // GT
    { {     271}, {  49} }, // GE
    { {       0}, { -20} },      
};


// State array:
SR__ *s_state[] =
{
  s_0,  s_1,  s_2,  s_3,  s_4,  s_5,  s_6,  s_7,  s_8,  s_9,
  s_10,  s_11,  s_12,  s_13,  s_14,  s_15,  s_16,  s_17,  s_18,  s_19,
  s_20,  s_21,  s_22,  s_23,  s_24,  s_25,  s_26,  s_27,  s_28,  s_29,
  s_30,  s_31,  s_32,  s_33,  s_34,  s_35,  s_36,  s_37,  s_38,  s_39,
  s_40,  s_41,  s_42,  s_43,  s_44,  s_45,  s_46,  s_47,  s_48,  s_49,
  s_50,  s_51,  s_52,  s_53,  s_54,  s_55,  s_56,  s_57,  s_58,  s_59,
};

} // anonymous namespace ends



// If the parsing function call uses arguments, then provide an overloaded
// function.  The code below doesn't rely on parameters, so no arguments are
// required.  Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called by actions,
// simply throwing the appropriate exceptions.

ParserBase::ParserBase()
:
    d_stackIdx__(-1),
    // $insert debuginit
    d_debug__(false),
    d_nErrors__(0),
    // $insert requiredtokens
    d_requiredTokens__(0),
    d_acceptedTokens__(d_requiredTokens__),
    d_token__(_UNDETERMINED_),
    d_nextToken__(_UNDETERMINED_)
{}


void ParserBase::clearin()
{
    d_token__ = d_nextToken__ = _UNDETERMINED_;
}

void ParserBase::push__(size_t state)
{
    if (static_cast<size_t>(d_stackIdx__ + 1) == d_stateStack__.size())
    {
        size_t newSize = d_stackIdx__ + STACK_EXPANSION;
        d_stateStack__.resize(newSize);
        d_valueStack__.resize(newSize);
    }
    ++d_stackIdx__;
    d_stateStack__[d_stackIdx__] = d_state__ = state;
    *(d_vsp__ = &d_valueStack__[d_stackIdx__]) = d_val__;
}

void ParserBase::popToken__()
{
    d_token__ = d_nextToken__;

    d_val__ = d_nextVal__;
    d_nextVal__ = STYPE__();

    d_nextToken__ = _UNDETERMINED_;
}
     
void ParserBase::pushToken__(int token)
{
    d_nextToken__ = d_token__;
    d_nextVal__ = d_val__;
    d_token__ = token;
}
     
void ParserBase::pop__(size_t count)
{
    if (d_stackIdx__ < static_cast<int>(count))
    {
        ABORT();
    }

    d_stackIdx__ -= count;
    d_state__ = d_stateStack__[d_stackIdx__];
    d_vsp__ = &d_valueStack__[d_stackIdx__];
}

inline size_t ParserBase::top__() const
{
    return d_stateStack__[d_stackIdx__];
}

void Parser::executeAction(int production)
{
    if (d_token__ != _UNDETERMINED_)
        pushToken__(d_token__);     // save an already available token

                                    // save default non-nested block $$
    if (int size = s_productionInfo[production].d_size)
        d_val__ = d_vsp__[1 - size];

    switch (production)
    {
        // $insert actioncases
        
        case 1:
        { 
         program_object.set_procedure_map(*current_procedure);
         if (d_vsp__[-3].symbol_table)
         d_vsp__[-3].symbol_table->global_list_in_proc_map_check(get_line_number());
         delete d_vsp__[-3].symbol_table;
         
         }
        break;

        case 2:
        d_val__ = d_vsp__[-1];
        { 
         program_object.set_global_table(*d_vsp__[-1].symbol_table);
         return_statement_used_flag = false; 
         
         }
        break;

        case 3:
        { 
         program_object.set_procedure_map(*current_procedure);
         
         }
        break;

        case 4:
        d_val__ = d_vsp__[0];
        { 
         return_statement_used_flag = false; 
         
         }
        break;

        case 5:
        { 
         current_procedure = new Procedure(void_data_type, *d_vsp__[-2].string_value);
         
         }
        break;

        case 6:
        { 
         if (return_statement_used_flag == false)
         {
         int line = get_line_number();
         report_error("Atleast 1 basic block should have a return statement", line);
         }
         current_procedure->set_basic_block_list(*d_vsp__[-1].basic_block_list);
         delete d_vsp__[-1].basic_block_list;
         
         }
        break;

        case 7:
        d_val__ = d_vsp__[-1];
        { 
         current_procedure->set_local_list(*d_vsp__[0].symbol_table);
         delete d_vsp__[0].symbol_table;
         
         }
        break;

        case 8:
        { 
         if (return_statement_used_flag == false)
         {
         int line = get_line_number();
         report_error("Atleast 1 basic block should have a return statement", line);
         }
         current_procedure->set_basic_block_list(*d_vsp__[-1].basic_block_list);
         delete d_vsp__[-1].basic_block_list;
         
         }
        break;

        case 9:
        { 
         int line = get_line_number();
         program_object.variable_in_proc_map_check(d_vsp__[0].symbol_entry->get_variable_name(), line);
         string var_name = d_vsp__[0].symbol_entry->get_variable_name();
         if (current_procedure && current_procedure->get_proc_name() == var_name)
         {
         int line = get_line_number();
         report_error("Variable name cannot be same as procedure name", line);
         }
         d_val__.symbol_table = new Symbol_Table();
         d_val__.symbol_table->push_symbol(d_vsp__[0].symbol_entry);
         
         }
        break;

        case 10:
        { 
         
         
         int line = get_line_number();
         program_object.variable_in_proc_map_check(d_vsp__[0].symbol_entry->get_variable_name(), line);
         string var_name = d_vsp__[0].symbol_entry->get_variable_name();
         if (current_procedure && current_procedure->get_proc_name() == var_name)
         {
         int line = get_line_number();
         report_error("Variable name cannot be same as procedure name", line);
         }
         if (d_vsp__[-1].symbol_table != NULL)
         {
         if(d_vsp__[-1].symbol_table->variable_in_symbol_list_check(var_name))
         {
         int line = get_line_number();
         report_error("Variable is declared twice", line);
         }
         d_val__.symbol_table = d_vsp__[-1].symbol_table;
         }
         else
         d_val__.symbol_table = new Symbol_Table();
         d_val__.symbol_table->push_symbol(d_vsp__[0].symbol_entry);
         
         }
        break;

        case 11:
        { 
         d_val__.symbol_entry = new Symbol_Table_Entry(*d_vsp__[-1].string_value, int_data_type);
         delete d_vsp__[-1].string_value;
         
         }
        break;

        case 12:
        { 
         
         if (!d_vsp__[0].basic_block)
         {
         int line = get_line_number();
         report_error("Basic block doesn't exist", line);
         }
         bb_strictly_increasing_order_check(d_val__.basic_block_list, d_vsp__[0].basic_block->get_bb_number());
         d_val__.basic_block_list = d_vsp__[-1].basic_block_list;
         d_val__.basic_block_list->push_back(d_vsp__[0].basic_block);
         
         }
        break;

        case 13:
        { 
         if (!d_vsp__[0].basic_block)
         {
         int line = get_line_number();
         report_error("Basic block doesn't exist", line);
         }
         d_val__.basic_block_list = new list<Basic_Block *>;
         d_val__.basic_block_list->push_back(d_vsp__[0].basic_block);
         
         }
        break;

        case 14:
        { 
         if ((*d_vsp__[-2].string_value).substr(1,2) != "bb")
         {
         int line = get_line_number();
         report_error("Not basic block lable", line);
         }
         if (atoi(((*d_vsp__[-2].string_value).substr(4,((*d_vsp__[-2].string_value).length()-5))).c_str()) < 2)
         {
         int line = get_line_number();
         report_error("Illegal basic block lable", line);
         }
         if (d_vsp__[0].ast_list != NULL)
         d_val__.basic_block = new Basic_Block(atoi(((*d_vsp__[-2].string_value).substr(4,((*d_vsp__[-2].string_value).length()-5))).c_str()), *d_vsp__[0].ast_list);
         else
         {
         list<Ast *> * ast_list = new list<Ast *>;
         d_val__.basic_block = new Basic_Block(atoi(((*d_vsp__[-2].string_value).substr(4,((*d_vsp__[-2].string_value).length()-5))).c_str()), *ast_list);
         }
         delete d_vsp__[0].ast_list;
         delete d_vsp__[-2].string_value;
         
         }
        break;

        case 15:
        {
         d_val__.ast = new Relational_Expr_Ast(d_vsp__[-2].ast, d_vsp__[0].ast, d_vsp__[-1].string_value);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         }
        break;

        case 16:
        {
         d_val__.ast = new Relational_Expr_Ast(d_vsp__[-2].ast, d_vsp__[0].ast, d_vsp__[-1].string_value);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         }
        break;

        case 17:
        {
         d_val__.ast = new Relational_Expr_Ast(d_vsp__[-2].ast, d_vsp__[0].ast, d_vsp__[-1].string_value);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         }
        break;

        case 18:
        {
         d_val__.ast = new Relational_Expr_Ast(d_vsp__[-2].ast, d_vsp__[0].ast, d_vsp__[-1].string_value);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         }
        break;

        case 19:
        {
         d_val__.ast = new Relational_Expr_Ast(d_vsp__[-2].ast, d_vsp__[0].ast, d_vsp__[-1].string_value);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         }
        break;

        case 20:
        {
         d_val__.ast = new Relational_Expr_Ast(d_vsp__[-2].ast, d_vsp__[0].ast, d_vsp__[-1].string_value);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         }
        break;

        case 21:
        {
         d_val__.ast = d_vsp__[0].ast;
         }
        break;

        case 22:
        {
         d_val__.ast=d_vsp__[0].ast;
         }
        break;

        case 23:
        { 
         d_val__.ast_list = d_vsp__[0].ast_list;
         
         }
        break;

        case 24:
        { 
         Ast * ret = new Return_Ast();
         return_statement_used_flag = true; 
         if (d_vsp__[-2].ast_list != NULL)
         d_val__.ast_list = d_vsp__[-2].ast_list;
         else
         d_val__.ast_list = new list<Ast *>;
         d_val__.ast_list->push_back(ret);
         
         }
        break;

        case 25:
        {
         Ast * ret = new Goto_Ast( atoi(((*d_vsp__[-1].string_value).substr(4,((*d_vsp__[-1].string_value).length()-5))).c_str()));
         if (d_vsp__[-3].ast_list != NULL)
         d_val__.ast_list = d_vsp__[-3].ast_list;
         else
         d_val__.ast_list = new list<Ast *>;
         d_val__.ast_list->push_back(ret);
         }
        break;

        case 26:
        { 
         d_val__.ast_list = NULL;
         
         }
        break;

        case 27:
        { 
         if (d_vsp__[-1].ast_list == NULL)
         d_val__.ast_list = new list<Ast *>;
         else
         d_val__.ast_list = d_vsp__[-1].ast_list;
         d_val__.ast_list->push_back(d_vsp__[0].ast);
         
         }
        break;

        case 28:
        { 
         d_val__.ast = new Assignment_Ast(d_vsp__[-3].ast, d_vsp__[-1].ast);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         
         }
        break;

        case 29:
        { 
         d_val__.ast = new Assignment_Ast(d_vsp__[-3].ast, d_vsp__[-1].ast);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         
         }
        break;

        case 30:
        {
         d_val__.ast = new Assignment_Ast(d_vsp__[-3].ast, d_vsp__[-1].ast);
         int line = get_line_number();
         d_val__.ast->check_ast(line);
         }
        break;

        case 31:
        { 
         Symbol_Table_Entry var_table_entry;
         if (current_procedure->variable_in_symbol_list_check(*d_vsp__[0].string_value))
         var_table_entry = current_procedure->get_symbol_table_entry(*d_vsp__[0].string_value);
         else if (program_object.variable_in_symbol_list_check(*d_vsp__[0].string_value))
         var_table_entry = program_object.get_symbol_table_entry(*d_vsp__[0].string_value);
         else
         {
         int line = get_line_number();
         report_error("Variable has not been declared", line);
         }
         d_val__.ast = new Name_Ast(*d_vsp__[0].string_value, var_table_entry);
         delete d_vsp__[0].string_value;
         
         }
        break;

        case 32:
        { 
         d_val__.ast = new Number_Ast<int>(d_vsp__[0].integer_value, int_data_type);
         
         }
        break;

    }
}

inline void ParserBase::reduce__(PI__ const &pi)
{
    d_token__ = pi.d_nonTerm;
    pop__(pi.d_size);

}

// If d_token__ is _UNDETERMINED_ then if d_nextToken__ is _UNDETERMINED_ another
// token is obtained from lex(). Then d_nextToken__ is assigned to d_token__.
void Parser::nextToken()
{
    if (d_token__ != _UNDETERMINED_)        // no need for a token: got one
        return;                             // already

    if (d_nextToken__ != _UNDETERMINED_)
    {
        popToken__();                       // consume pending token
    }
    else
    {
        ++d_acceptedTokens__;               // accept another token (see
                                            // errorRecover())
        d_token__ = lex();
        if (d_token__ <= 0)
            d_token__ = _EOF_;
    }
    print();
}

// if the final transition is negative, then we should reduce by the rule
// given by its positive value. Note that the `recovery' parameter is only
// used with the --debug option
int Parser::lookup(bool recovery)
{
    // $insert threading
    SR__ *sr = s_state[d_state__];        // get the appropriate state-table
    int lastIdx = sr->d_lastIdx;        // sentinel-index in the SR__ array

    SR__ *lastElementPtr = sr + lastIdx;
    SR__ *elementPtr = sr + 1;            // start the search at s_xx[1]

    lastElementPtr->d_token = d_token__;// set search-token

    while (elementPtr->d_token != d_token__)
        ++elementPtr;

    if (elementPtr == lastElementPtr)   // reached the last element
    {
        if (elementPtr->d_action < 0)   // default reduction
        {
            return elementPtr->d_action;                
        }

        // No default reduction, so token not found, so error.
        throw UNEXPECTED_TOKEN__;
    }

    // not at the last element: inspect the nature of the action
    // (< 0: reduce, 0: ACCEPT, > 0: shift)

    int action = elementPtr->d_action;


    return action;
}

    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)
void Parser::errorRecovery()
try
{
    if (d_acceptedTokens__ >= d_requiredTokens__)// only generate an error-
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error("Syntax error");                  // simply skip input

    }


    // get the error state
    while (not (s_state[top__()][0].d_type & ERR_ITEM))
    {
        pop__();
    }

    // In the error state, lookup a token allowing us to proceed.
    // Continuation may be possible following multiple reductions,
    // but eventuall a shift will be used, requiring the retrieval of
    // a terminal token. If a retrieved token doesn't match, the catch below 
    // will ensure the next token is requested in the while(true) block
    // implemented below:

    int lastToken = d_token__;                  // give the unexpected token a
                                                // chance to be processed
                                                // again.

    pushToken__(_error_);                       // specify _error_ as next token
    push__(lookup(true));                       // push the error state

    d_token__ = lastToken;                      // reactivate the unexpected
                                                // token (we're now in an
                                                // ERROR state).

    bool gotToken = true;                       // the next token is a terminal

    while (true)
    {
        try
        {
            if (s_state[d_state__]->d_type & REQ_TOKEN)
            {
                gotToken = d_token__ == _UNDETERMINED_;
                nextToken();                    // obtain next token
            }
            
            int action = lookup(true);

            if (action > 0)                 // push a new state
            {
                push__(action);
                popToken__();

                if (gotToken)
                {

                    d_acceptedTokens__ = 0;
                    return;
                }
            }
            else if (action < 0)
            {
                // no actions executed on recovery but save an already 
                // available token:
                if (d_token__ != _UNDETERMINED_)
                    pushToken__(d_token__);
 
                                            // next token is the rule's LHS
                reduce__(s_productionInfo[-action]); 
            }
            else
                ABORT();                    // abort when accepting during
                                            // error recovery
        }
        catch (...)
        {
            if (d_token__ == _EOF_)
                ABORT();                    // saw inappropriate _EOF_
                      
            popToken__();                   // failing token now skipped
        }
    }
}
catch (ErrorRecovery__)       // This is: DEFAULT_RECOVERY_MODE
{
    ABORT();
}

    // The parsing algorithm:
    // Initially, state 0 is pushed on the stack, and d_token__ as well as
    // d_nextToken__ are initialized to _UNDETERMINED_. 
    //
    // Then, in an eternal loop:
    //
    //  1. If a state does not have REQ_TOKEN no token is assigned to
    //     d_token__. If the state has REQ_TOKEN, nextToken() is called to
    //      determine d_nextToken__ and d_token__ is set to
    //     d_nextToken__. nextToken() will not call lex() unless d_nextToken__ is 
    //     _UNDETERMINED_. 
    //
    //  2. lookup() is called: 
    //     d_token__ is stored in the final element's d_token field of the
    //     state's SR_ array. 
    //
    //  3. The current token is looked up in the state's SR_ array
    //
    //  4. Depending on the result of the lookup() function the next state is
    //     shifted on the parser's stack, a reduction by some rule is applied,
    //     or the parsing function returns ACCEPT(). When a reduction is
    //     called for, any action that may have been defined for that
    //     reduction is executed.
    //
    //  5. An error occurs if d_token__ is not found, and the state has no
    //     default reduction. Error handling was described at the top of this
    //     file.

int Parser::parse()
try 
{
    push__(0);                              // initial state
    clearin();                              // clear the tokens.

    while (true)
    {
        try
        {
            if (s_state[d_state__]->d_type & REQ_TOKEN)
                nextToken();                // obtain next token


            int action = lookup(false);     // lookup d_token__ in d_state__

            if (action > 0)                 // SHIFT: push a new state
            {
                push__(action);
                popToken__();               // token processed
            }
            else if (action < 0)            // REDUCE: execute and pop.
            {
                executeAction(-action);
                                            // next token is the rule's LHS
                reduce__(s_productionInfo[-action]); 
            }
            else 
                ACCEPT();
        }
        catch (ErrorRecovery__)
        {
            errorRecovery();
        }
    }
}
catch (Return__ retValue)
{
    return retValue;
}

