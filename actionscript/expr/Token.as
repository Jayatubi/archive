package expr
{
    
    public class Token
    {
        public static const NA : int = -1;
        public static const BUILDINVALUE : int = 0;
        public static const NUMBER : int = 1;
        public static const STRING : int = 2;
        public static const VARIABLE : int = 3;
        public static const FUNCTION : int = 4;
        public static const OPERATOR : int = 5;
        public static const SPLITER : int = 6;
        
        private var m_type : int;
        private var m_symbol : String;
        private var m_index : uint;
        private var m_argcount : uint;
        private var m_argindex : uint;
        
        public function Token(type : int, symbol : String)
        {
            m_type = type;
            m_symbol = symbol;
            m_argcount = 0;
        }
        
        public function get type() : int
        {
            return m_type;
        }
        
        public function get symbol() : String
        {
            return m_symbol;
        }
        
        public function get index() : uint
        {
            return m_index;
        }
        
        public function set index(value : uint) : void
        {
            m_index = value;
        }
        
        public function get argcount() : uint
        {
            return m_argcount;
        }
        
        public function set argcount(value : uint) : void
        {
            m_argcount = value;
        }
        
        public function get argindex() : uint
        {
            return m_argindex;
        }
        
        public function set argindex(value : uint) : void
        {
            m_argindex = value;
        }
        
        public function toString() : String
        {
            var typeStr : String = "unkonwn";
            
            switch (m_type)
            {
                case NA: 
                    typeStr = "undefined";
                    break;
                case BUILDINVALUE: 
                    typeStr = "buildin";
                    break;
                case NUMBER: 
                    typeStr = "number";
                    break;
                case STRING: 
                    typeStr = "string";
                    break;
                case VARIABLE: 
                    typeStr = "variable";
                    break;
                case FUNCTION: 
                    typeStr = "function";
                    break;
                case OPERATOR: 
                    typeStr = "operator";
                    break;
                case SPLITER: 
                    typeStr = "spliter";
                    break;
            }
            
            return "Index: " + m_index + " Type: " + typeStr + ", Symbol: " + m_symbol + ", Args: [" + m_argindex + ", " + m_argcount + "]";
        }
    }
}