package expr
{
    
    public dynamic class ArrayEx extends Array
    {
        public function ArrayEx(... args)
        {
            for each (var iterator : Array in args)
            {
                Insert(iterator);
            }
        }
        
        public function Insert(src : Array) : void
        {
            for each (var iterator : Object in src)
            {
                push(iterator);
            }
        }
        
        public function get first() : Object
        {
            return this[0];
        }
        
        public function set first(value : Object) : void
        {
            this[0] = value;
        }
        
        public function get last() : Object
        {
            return this[length - 1];
        }
        
        public function set last(value : Object) : void
        {
            this[length - 1] = value;
        }
        
        public function get empty() : Boolean
        {
            return length == 0;
        }
        
        public function contains(element : Object) : Boolean
        {
            for each (var iterator : Object in this)
            {
                if (iterator == element)
                    return true;
            }
            return false;
        }
    
    }

}