from enum import Enum
import numpy as np
class WhichFunction(Enum):
    W_add = 0,
    W_minus = 1,
    W_times = 2,
    W_divide = 3,
    W_sin = 4,
    W_cos = 5,
    W_tan = 6,
    W_asin = 7,
    W_acos = 8,
    W_atan = 9,
    W_atan2 = 10,
    W_pow = 11,
    W_square = 12,
    W_cube = 13,
    W_sqrt = 14,
    W_log2 = 15,
    W_log10 = 16,
    W_max = 17,
    W_min = 18,
    W_ex = 19

functionArgMap = {WhichFunction.W_add:(2,"add"),WhichFunction.W_minus:(2,"miuns"),
                  WhichFunction.W_times:(2,"times"),WhichFunction.W_divide:(2,"divide"),
                  WhichFunction.W_sin:(1,"sin"),WhichFunction.W_cos:(1,"cos"),
                  WhichFunction.W_tan:(1,"tan"),WhichFunction.W_asin:(1,"asin"),
                  WhichFunction.W_acos:(1,"acos"),WhichFunction.W_atan:(1,"atan"),
                  WhichFunction.W_atan2:(2,"atan2"),WhichFunction.W_pow:(2,"pow"),
                  WhichFunction.W_square:(1,"square"),WhichFunction.W_cube:(1,"cube"),
                  WhichFunction.W_sqrt:(1,"sqrt"),WhichFunction.W_log2:(1,"log2"),
                  WhichFunction.W_log10:(1,"log10"),WhichFunction.W_max:(2,"max"),
                  WhichFunction.W_min:(2,"min"),WhichFunction.W_ex:(1,"exp")}

functionNumVec = [WhichFunction.W_add,WhichFunction.W_minus,
                  WhichFunction.W_times,WhichFunction.W_divide,
                  WhichFunction.W_sin,WhichFunction.W_cos,
                  WhichFunction.W_tan,WhichFunction.W_asin,
                  WhichFunction.W_acos,WhichFunction.W_atan,
                  WhichFunction.W_atan2,WhichFunction.W_pow,
                  WhichFunction.W_square,WhichFunction.W_cube,
                  WhichFunction.W_sqrt,WhichFunction.W_log2,
                  WhichFunction.W_log10,WhichFunction.W_max,
                  WhichFunction.W_min,WhichFunction.W_ex]


def functionPresetHandler(args,whichFunction):
    try:
        if whichFunction == WhichFunction.W_add:
            return args[0] + args[1]
        elif whichFunction == WhichFunction.W_minus:
            return args[0] - args[1]
        elif whichFunction == WhichFunction.W_times:
            return args[0] * args[1]
        elif whichFunction == WhichFunction.W_divide:
            if args[1] == 0:
                raise ValueError("error : divide zero!!")
            else:
                return args[0] / args[1]
        elif whichFunction == WhichFunction.W_sin:
            return np.sin(args[0])
        elif whichFunction == WhichFunction.W_cos:
            return np.cos(args[0])
        elif whichFunction == WhichFunction.W_tan:
            return np.tan(args[0])
        elif whichFunction == WhichFunction.W_asin:
            return np.arcsin(args[0])
        elif whichFunction == WhichFunction.W_acos:
            return np.arccos(args[0])
        elif whichFunction == WhichFunction.W_atan:
            return np.arctanh(args[0])
        elif whichFunction == WhichFunction.W_atan2:
            return np.arctan2(args[0],args[1])
        elif whichFunction == WhichFunction.W_pow:
            return np.power(args[0],args[1])
        elif whichFunction == WhichFunction.W_square:
            return args[0] * args[0]
        elif whichFunction == WhichFunction.W_cube:
            return args[0] * args[0] * args[0]
        elif whichFunction == WhichFunction.W_sqrt:
            return np.sqrt(args[0])
        elif whichFunction == WhichFunction.W_log2:
            return np.log2(args[0])
        elif whichFunction == WhichFunction.W_log10:
            return np.log10(args[0])
        elif whichFunction == WhichFunction.W_max:
            return max(args[0],args[1])
        elif whichFunction == WhichFunction.W_min:
            return min(args[0],args[1])
        elif whichFunction == WhichFunction.W_ex:
            return np.exp(args[0])
        else:
            raise ValueError("error : no such function which is preseted!")
    except ValueError as e:
        print(repr(e))
        exit(-1)
