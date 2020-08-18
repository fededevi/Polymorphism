#ifndef MAIN_H
#define MAIN_H

typedef enum  {
    EXPRESSION_SUM=0,
    EXPRESSION_MUL,
    EXPRESSION_INT,
    EXPRESSION_VAR,
    EXPRESSION_TYPE_COUNT
} ExpressionType;

typedef struct {
} Dog;

typedef struct {
    void * exp;
    ExpressionType type;
} Expression;

typedef struct {
    Expression l;
    Expression r;
} DualOperator;

typedef struct {
    DualOperator ops;
} Sum;

typedef struct {
    DualOperator ops;
} Mul;

typedef struct {
    int value;
} Int;

typedef struct {
    char name[10];
} Var;


Expression evalSum ( Expression e );

Expression evalMul ( Expression e );

Expression evalInt ( Expression e );

Expression evalVar ( Expression e );



#endif // MAIN_H
