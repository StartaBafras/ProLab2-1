typedef struct variable_s
{

    char name[10];
    int kind;
    int line;
    int increase_rate;

}variable_s;

typedef struct veriable_s_pointer
{
    variable_s *variable; 
    variable_s *next;
}veriable_s_pointer;

typedef struct loop_s_pointer
{
    variable_s *loop; 
    variable_s *next;
}loop_s_pointer;

typedef struct function_s_pointer
{
    function_s *loop; 
    function_s *next;

}function_s_pointer;

typedef struct loop_s
{
    int id;
    int kind;
    int start_end_line[2];
    veriable_s_pointer dependent_variable;
    int complexity;
    
}loop_s;

typedef struct function_s
{
    char name[20];
    int start_end_line[2];
    loop_s_pointer loops_inside;
    function_s_pointer function_inside;
    int complexity;
    int amount_call;
    int call_line;

}function_s;

