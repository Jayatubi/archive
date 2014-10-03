package expr
{
    
    public class Evaluater
    {
        private var m_outputstack : ArrayEx;
        private var m_variablePool : Object;
        private var m_rawCode : String;
        private static var s_funcmap : Object = {};
        private static const OPER_ARGCOUNT : Object = {'!': 1, '^': 2, '*': 2, '/': 2, '%': 2, '+': 2, '-': 2, '&' : 2, '|' : 2, '#' : 2, '<': 2, '>': 2, '<=': 2, '>=': 2, '==': 2, '!=': 2, '&&': 2, '||': 2, '?': 1, ':': 3};
        private static const OPER_PRIORITY : Object = {'!': 0, '^': 1, '*': 2, '/': 2, '%': 2, '+': 3, '-': 3, '&' : 3, '|' : 3, '#' : 3, '<': 4, '>': 4, '<=': 4, '>=': 4, '==': 5, '!=': 5, '&&': 6, '||': 7, '?': 8, ':': 9};
        
        public function Evaluater(code : String)
        {
            try
            {
                m_rawCode = code;
                buildStack(code);
            }
            catch (e : Error)
            {
                trace("Error occured when parsing: " + code);
                trace(e.message);
            }
        }
        
        public function toString() : String
        {
            return "Output Stack:\n  " + m_outputstack.join("\n  ");
        }
        
        private function buildStack(code : String) : void
        {
            var topoper : Token;
            m_outputstack = new ArrayEx();
            
            var operatorstack : ArrayEx = new ArrayEx();
            var argcollector : ArrayEx = new ArrayEx();
            
            var parser : Parser = new Parser(code);
            
            for each (var token : Token in parser.tokens)
            {
                switch (token.type)
                {
                    case Token.BUILDINVALUE: 
                    case Token.NUMBER: 
                    case Token.STRING: 
                    case Token.VARIABLE: 
                        m_outputstack.push(token);
                        if (!argcollector.empty && argcollector.last == 0)
                        {
                            argcollector.last = 1;
                        }
                        break;
                    case Token.FUNCTION: 
                        operatorstack.push(token);
                        if (!argcollector.empty && argcollector.last == 0)
                        {
                            argcollector.last = 1;
                        }
                        break;
                    case Token.OPERATOR:
                        token.argcount = OPER_ARGCOUNT[token.symbol];
                        while (!operatorstack.empty)
                        {
                            topoper = operatorstack.last as Token;
                            
                            if (topoper.type == Token.FUNCTION)
                            {
                                topoper.argindex = m_outputstack.length - 1;
                                m_outputstack.push(topoper);
                                operatorstack.pop()
                            }
                            else if (topoper.type == Token.OPERATOR)
                            {
                                var topprio : uint = OPER_PRIORITY[topoper.symbol];
                                var thisprio : uint = OPER_PRIORITY[token.symbol];
                                
                                if (!isNaN(topprio) && !isNaN(thisprio))
                                {
                                    if (topprio <= thisprio)
                                    {
                                        topoper.argindex = m_outputstack.length - 1;
                                        m_outputstack.push(topoper);
                                        operatorstack.pop();
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    throw new Error("Syntax erorr around '" + token.symbol + "'");
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        operatorstack.push(token);
                        break;
                    case Token.SPLITER: 
                        if (token.symbol == "(")
                        {
                            if (!operatorstack.empty)
                            {
                                topoper = operatorstack.last as Token;
                                
                                if (topoper.type == Token.FUNCTION)
                                {
                                    argcollector.push(0);
                                }
                                else
                                {
                                    argcollector.push(null);
                                }
                            }
                            operatorstack.push(token);
                        }
                        else if (token.symbol == ")")
                        {
                            while (!operatorstack.empty)
                            {
                                topoper = operatorstack.pop();
                                
                                if (topoper.symbol != "(")
                                {
                                    topoper.argindex = m_outputstack.length - 1;
                                    m_outputstack.push(topoper);
                                }
                                else
                                {
                                    break;
                                }
                            }
                            
                            if (!operatorstack.empty)
                            {
                                topoper = operatorstack.last as Token;
                                
                                if (topoper.type == Token.FUNCTION)
                                {
                                    topoper.argcount = argcollector.pop();
                                    topoper.argindex = m_outputstack.length - 2;
                                }
                                else
                                {
                                    argcollector.pop();
                                }
                            }
                        }
                        else if (token.symbol == ",")
                        {
                            if (!argcollector.empty && argcollector.last != null)
                            {
                                argcollector.last = (argcollector.last as uint) + 1;
                            }
                            
                            while (!operatorstack.empty)
                            {
                                topoper = operatorstack.last as Token
                                
                                if (topoper.symbol != "(")
                                {
                                    m_outputstack.push(topoper);
                                    operatorstack.pop();
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        break;
                }
            }
            
            while (!operatorstack.empty)
            {
                topoper = operatorstack.pop();
                
                if (topoper.symbol == '(')
                {
                    throw new Error("Missing ')'");
                }
                topoper.argindex = m_outputstack.length - 1;
                m_outputstack.push(topoper);
            }
            
            for (var i : uint = 0; i < m_outputstack.length; i++)
            {
                (m_outputstack[i] as Token).index = i;
            }
        }
        
        public function evaluate(variable : Object) : Object
        {
            m_variablePool = variable;
            return evaluateToken(m_outputstack.last as Token);
        }
        
        private function evaluateToken(token : Token) : Object
        {
            switch (token.type)
            {
                case Token.BUILDINVALUE: 
                    return token.symbol != "this" ? BuildinValue.VALUES[token.symbol] : m_variablePool;
                case Token.NUMBER: 
                    return Number(token.symbol);
                case Token.STRING: 
                    return token.symbol.substr(1, token.symbol.length - 2);
                case Token.VARIABLE: 
                {
                    var varName : String = token.symbol.substr(1);
                    var allowNull : Boolean = false;
                    
                    if (varName.charAt(0) == '?')
                    {
                        varName = varName.substr(1);
                        allowNull = true;
                    }
                    
                    // [zkyang] Do we really need to always allow null?
                    allowNull = true;
                    
                    var value : * = null;
                    var subNames : Array = varName.split(".");
                    
                    for (var i = 0; i < subNames.length; i++)
                    {
                        if (i == 0)
                        {
                            value = m_variablePool[subNames[i]];
                        }
                        else
                        {
                            value = value[subNames[i]];
                        }
                        if (value == null)
                        {
                            break;
                        }
                    }
                    
                    if (value == null)
                    {
                        if (allowNull)
                            return null;
                        else
                            throw new Error("Undefined variable '" + token.symbol + "'");
                    }
                    else
                    {
                        return value;
                    }
                }
                case Token.FUNCTION: 
                    return evaluateFunctionToken(token);
                case Token.OPERATOR: 
                    return evaluateOperatorToken(token);
                default: 
                    return null;
            }
        }
        
        private function evaluateOperatorToken(token : Token) : *
        {
            var oprand1 : *;
            var oprand2 : *;
            var oprand3 : *;
            
            switch (token.symbol)
            {
                case '!': 
                {
                    oprand1 = firstArgToken(token);
                    return !evaluateToken(oprand1);
                }
                    break;
                case '^': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return Math.pow(Number(evaluateToken(oprand1)), Number(evaluateToken(oprand2)));
                }
                    break;
                case '*': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return Number(evaluateToken(oprand1)) * Number(evaluateToken(oprand2));
                }
                    break;
                case '/': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return Number(evaluateToken(oprand1)) / Number(evaluateToken(oprand2));
                }
                    break;
                case '%': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return Number(evaluateToken(oprand1)) % Number(evaluateToken(oprand2));
                }
                    break;
                case '+': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) + evaluateToken(oprand2);
                }
                    break;
                case '-': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return Number(evaluateToken(oprand1)) - Number(evaluateToken(oprand2));
                }
                    break;
                case '&': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return int(evaluateToken(oprand1)) & int(evaluateToken(oprand2));
                }
                    break;
                case '|': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return int(evaluateToken(oprand1)) | int(evaluateToken(oprand2));
                }
                    break;
                case '#': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return int(evaluateToken(oprand1)) ^ int(evaluateToken(oprand2));
                }
                    break;
                case '<': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) < evaluateToken(oprand2);
                }
                    break;
                case '>': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) > evaluateToken(oprand2);
                }
                    break;
                case '<=': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) <= evaluateToken(oprand2);
                }
                    break;
                case '>=': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) >= evaluateToken(oprand2);
                }
                    break;
                case '==': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) == evaluateToken(oprand2);
                }
                    break;
                case '!=': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) != evaluateToken(oprand2);
                }
                    break;
                case '&&': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) && evaluateToken(oprand2);
                }
                    break;
                case '||': 
                {
                    oprand2 = firstArgToken(token);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) || evaluateToken(oprand2);
                }
                    break;
                case '?': 
                {
                    oprand1 = firstArgToken(token);
                    return evaluateToken(oprand1);
                }
                    break;
                case ':': 
                {
                    oprand3 = firstArgToken(token);
                    oprand2 = nextArgToken(oprand3);
                    oprand1 = nextArgToken(oprand2);
                    return evaluateToken(oprand1) ? evaluateToken(oprand2) : evaluateToken(oprand3);
                }
                    break;
                default: 
                    break;
            }
            
            throw new Error("Illegal operator '" + token.symbol + "'");
            return undefined;
        }
        
        private function evaluateFunctionToken(token : Token) : Object
        {
            var i : uint;
            var func : Function = s_funcmap[token.symbol];
            
            if (func != null)
            {
                var args : ArrayEx = new ArrayEx();
                
                for (i = 0; i < token.argcount; i++)
                {
                    if (i == 0)
                        args.unshift(firstArgToken(token));
                    else
                        args.unshift(nextArgToken(args.first as Token));
                }
                
                for (i = 0; i < token.argcount; i++)
                {
                    args[i] = evaluateToken(args[i]);
                }
                
                return func.apply(null, args);
            }
            else
            {
                throw new Error("Undefined function '" + token.symbol + "'");
            }
        }
        
        private function firstArgToken(token : Token) : Token
        {
            return m_outputstack[token.index - 1] as Token;
        }
        
        private function nextArgToken(token : Token) : Token
        {
            return m_outputstack[token.index - tokenLength(token)] as Token;
        }
        
        private function tokenLength(token : Token) : uint
        {
            var result : Number = 1;
            
            for (var i : uint = 0; i < token.argcount; i++)
            {
                var nextToken : Token = m_outputstack[token.index - result] as Token;
                result += tokenLength(nextToken);
            }
            
            return result;
        }
        
        public static function registerFunc(name : String, func : Function) : void
        {
            s_funcmap[name] = func;
        }
        
        public static function outputFuncs() : void
        {
            for (var i in s_funcmap)
            {
                trace(i + " : " + s_funcmap[i]);
            }
        }
        
        public function get rawCode():String 
        {
            return m_rawCode;
        }
    }
}