package expr
{
    
    public class Parser
    {
        private var m_code : String;
        private var m_seeker : uint;
        
        private var m_tokens : Array;
        private var m_lastToken : Token;
        
        public function get tokens() : Array
        {
            return m_tokens;
        }
        
        public function Parser(code : String)
        {
            m_code = code;
            Tokenize();
        }
        
        public function toString() : String
        {
            return "Code: " + m_code + "\nTokens:\n  " + m_tokens.join("\n  ");
        }
        
        private function Tokenize() : void
        {
            m_tokens = [];
            m_seeker = 0;
            
            while (hasNext())
            {
                if (getWhite() || getIgnore())
                {
                    
                }
                else if (getBuildinValue() || getNumber() || getString() || getVariable() || getFunction() || getOperator() || getSpliter())
                {
                    m_tokens.push(m_lastToken);
                }
                else
                {
                    throw new Error("EXPR: Unexpected character '" + getChar() + "'");
                }
            }
        }
        
        private function hasNext() : Boolean
        {
            return m_seeker < m_code.length;
        }
        
        private function getChar(offset : uint = 0) : String
        {
            return m_code.charAt(m_seeker + offset);
        }
        
        private function getWord(length : uint, offset : uint = 0) : String
        {
            return m_code.substr(m_seeker + offset, length);
        }
        
        private function next(step : uint = 1) : Boolean
        {
            m_seeker += step;
            return hasNext();
        }
        
        private function getWhite() : Boolean
        {
            var result : Boolean = false;
            
            do
            {
                var ch : String = getChar();
                
                if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
                    result = true;
                else
                    break;
            } while (next())
            
            return result;
        }
        
        private function getIgnore() : Boolean
        {
            var result : Boolean = false;
            
            do
            {
                var ch : String = getChar();
                
                if (ch == '#')
                    result = true;
                else
                    break;
            } while (next())
            
            return result;
        }
        
        private function getBuildinValue() : Boolean
        {
            var result : Boolean = false;
            
            for (var symbol : String in BuildinValue.VALUES)
            {
                if (symbol == getWord(symbol.length))
                {
                    result = true;
                    next(symbol.length);
                    m_lastToken = new Token(Token.BUILDINVALUE, symbol);
                    break;
                }
            }
            
            return result;
        }
        
        private function getNumber() : Boolean
        {
            var result : Boolean = false;
            var start : uint = m_seeker;
            var end : uint = m_seeker;
            
            do
            {
                var ch : String = getChar();
                if (ch == '.' || (ch >= '0' && ch <= '9'))
                    result = true;
                else
                    break;
            } while (next());
            
            if (result)
            {
                end = m_seeker;
                var symbol : String = m_code.substr(start, end - start);
                m_lastToken = new Token(Token.NUMBER, symbol);
            }
            
            return result;
        }
        
        private function getString() : Boolean
        {
            var result : Boolean = false;
            var start : uint = m_seeker;
            var end : uint = m_seeker;
            
            do
            {
                var ch : String = getChar();
                
                if (m_seeker == start)
                {
                    if (ch != '"')
                        break;
                }
                
                if (m_seeker != start)
                {
                    if (ch == '"')
                    {
                        next();
                        result = true;
                        break;
                    }
                }
            } while (next());
            
            if (result)
            {
                end = m_seeker;
                var symbol : String = m_code.substr(start, end - start);
                m_lastToken = new Token(Token.STRING, symbol);
            }
            
            return result;
        }
        
        private function getVariable() : Boolean
        {
            var result : Boolean = false;
            var start : uint = m_seeker;
            var end : uint = m_seeker;
            
            do
            {
                var ch : String = getChar();
                
                if (m_seeker == start)
                {
                    if (ch != '$')
                        break;
                }
                
                if (m_seeker != start)
                {
                    if (ch == '_' || ch == '?' || ch == '.' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
                    {
                        result = true;
                    }
                    else
                    {
                        break;
                    }
                }
            } while (next());
            
            if (result)
            {
                end = m_seeker;
                var symbol : String = m_code.substr(start, end - start);
                m_lastToken = new Token(Token.VARIABLE, symbol);
            }
            
            return result;
        }
        
        private function getFunction() : Boolean
        {
            var result : Boolean = false;
            var start : uint = m_seeker;
            var end : uint = m_seeker;
            
            do
            {
                var ch : String = getChar();
                
                if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
                {
                    result = true;
                }
                else
                {
                    break;
                }
            } while (next());
            
            if (result)
            {
                end = m_seeker;
                var symbol : String = m_code.substr(start, end - start);
                m_lastToken = new Token(Token.FUNCTION, symbol);
            }
            
            return result;
        }
        
        private function getOperator() : Boolean
        {
            var result : Boolean = false;
            var start : uint = m_seeker;
            var end : uint = m_seeker;
            
            const operators : String = "+-*/%^><=!&|?:#";
            
            do
            {
                var ch : String = getChar();
                
                if (operators.indexOf(ch) >= 0)
                {
                    result = true;
                }
                else
                {
                    break;
                }
            } while (next());
            
            if (result)
            {
                end = m_seeker;
                var symbol : String = m_code.substr(start, end - start);
                m_lastToken = new Token(Token.OPERATOR, symbol);
            }
            
            return result;
        }
        
        private function getSpliter() : Boolean
        {
            var result : Boolean = false;
            var start : uint = m_seeker;
            var end : uint = m_seeker;
            
            const spliters : String = "(),";
            
            do
            {
                var ch : String = getChar();
                
                if (spliters.indexOf(ch) >= 0)
                {
                    result = true;
                }
                next();
                break;
            } while (false);
            
            if (result)
            {
                end = m_seeker;
                var symbol : String = m_code.substr(start, end - start);
                m_lastToken = new Token(Token.SPLITER, symbol);
            }
            
            return result;
        }
    }
}