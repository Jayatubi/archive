package expr 
{
    public class Template 
    {
        private var m_segments : Array;
        private static const L_TAG:String = "<%";
        private static const R_TAG:String = "%>";
        
        public function Template(raw : String)
        {
            parse(raw);
        }
        
        private function parse(raw : String) : void
        {
            var lIndex : int = 0;
            var rIndex : int = 0;
            var lastRIndex : int = 0;
            
            m_segments = [];
            
            while (true)
            {
                lIndex = raw.indexOf(L_TAG, rIndex);
                rIndex = raw.indexOf(R_TAG, lIndex);
                
                if (lIndex >= 0 && rIndex >= 0)
                {
                    m_segments.push(raw.substring(lastRIndex, lIndex));             // Const
                    m_segments.push(raw.substring(lIndex + L_TAG.length, rIndex));  // Variable
                    lastRIndex = rIndex + R_TAG.length;
                }
                else
                {
                    if (lastRIndex < raw.length)
                    {
                        m_segments.push(raw.substring(lastRIndex));
                    }
                    break;
                }
            }
        }
        
        public function get segments():Array 
        {
            return m_segments;
        }
    }
}