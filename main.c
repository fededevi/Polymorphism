#include <stdio.h>
#include <stdlib.h>
#include <main.h>

Expression sumAsExp(Sum * e) { return (Expression){.exp=e, .type=EXPRESSION_SUM}; }
Expression mulAsExp(Mul * e) { return (Expression){.exp=e, .type=EXPRESSION_MUL}; }
Expression intAsExp(Int * e) { return (Expression){.exp=e, .type=EXPRESSION_INT}; }
Expression varAsExp(Var * e) { return (Expression){.exp=e, .type=EXPRESSION_VAR}; }

Expression (*evaluator[EXPRESSION_TYPE_COUNT])(Expression)={&evalSum, &evalMul, &evalInt, &evalVar};

Expression evalSum ( Expression e ) {
    Sum * s = (Sum *) e.exp;
    Expression l = evaluator[s->ops.l.type](s->ops.l);
    Expression r = evaluator[s->ops.r.type](s->ops.r);

    if (l.type == EXPRESSION_INT && r.type == EXPRESSION_INT) {
        //Return a value if both operands are int
        //TODO: delete l and
        Int * i = (Int *) malloc(sizeof(Int));
        Int * li = (Int *)l.exp;
        Int * ri = (Int *)r.exp;
        i->value = li->value + ri->value; //Set the value
        free(l.exp);
        free(r.exp);
        return intAsExp(i);
    } else {
        //Can't compute value return new sum
        Sum * s = (Sum *) malloc(sizeof(Sum));
        s->ops.l = l;
        s->ops.r = r;
        return sumAsExp(s);
    }
}

Expression evalMul ( Expression e ) {
    Mul * m = (Mul *) e.exp;
    Expression l = evaluator[m->ops.l.type](m->ops.l);
    Expression r = evaluator[m->ops.r.type](m->ops.r);

    if (l.type == EXPRESSION_INT && r.type == EXPRESSION_INT) {
        //Return a value if both operands are int
        Int * i = (Int *) malloc(sizeof(Int));
        Int * li = (Int *)l.exp;
        Int * ri = (Int *)r.exp;
        i->value = li->value * ri->value; //Set the value
        free(l.exp);
        free(r.exp);
        return intAsExp(i);
    } else {
        //Can't compute value return new sum
        Mul * i = (Mul *) malloc(sizeof(Mul));
        i->ops.l = l;
        i->ops.r = r;
        return mulAsExp(i);
    }
}

Expression evalInt ( Expression e ) {
    Int * i = (Int *) malloc(sizeof(Int));
    Int * ei = (Int *)(e.exp);
    i->value = ei->value;
    return intAsExp(i);
}

Expression evalVar ( Expression e ) {
    Var * v = (Var *) malloc(sizeof(Var));
    Var * ei = (Var *)(e.exp);
    for (int i = 0; i<10; i++)
        v->name[i] = ei->name[i];
    return varAsExp(v);
}

int main()
{
//Building the expression: 2 * (2 + 5)
Int i0 = {2};
Int i1 = {2};
Int i2 = {5};
Sum s1 = {intAsExp(&i1),intAsExp(&i2)};
Mul m1 = {intAsExp(&i0),sumAsExp(&s1)};

//Get the generic
Expression e = mulAsExp(&m1);

//Eval the expression
Expression evaluated = evaluator[e.type](e);

if (evaluated.type == EXPRESSION_INT)
{
    Int * i = (Int *)evaluated.exp;
    printf("Result: %i\n", i->value);
}

}