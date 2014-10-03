package expr
{
    
    public class TextRenderer
    {
        private static var s_cachedEvaluater : Object = { };
        private static var s_cachedTemplate : Object = { };
        private static var s_vairableStack : ArrayEx = new ArrayEx();
        
        public static function render(templateRaw:String, variable:Object = null):String
        {
            var actualVariable;
            
            // [zkyang] Primitives
            if (variable is int || variable is uint || variable is String || variable is Boolean)
            {
                actualVariable = { __Value : variable };
            }
            else if (variable != null && variable.hasOwnProperty("__enumerable"))
            {
                actualVariable = variable["__enumerable"];
            }
            else if (variable != null)
            {
                actualVariable = variable;
            }
            
            if (actualVariable != null)
            {
                s_vairableStack.push(actualVariable);
            }
            
            var result : String = "";
            if (templateRaw != null)
            {
                var template : Template = acquireTemplate(templateRaw);
                
                for (var i = 0; i < template.segments.length; i++)
                {
                    var theSegment : String = template.segments[i];
                    if (theSegment.length > 0)
                    {
                        if ((i & 1) != 0)
                        {
                            var value : String = "";
                            var evaluater : Evaluater = acquireEvaluater(theSegment);
                            try
                            {
                                var evalResult : Object = evaluater.evaluate((s_vairableStack.length > 0) ? s_vairableStack.last : { } ) as Object;
                                value = evalResult != null ? evalResult.toString() : "";
                            }
                            catch (e : Error)
                            {
                                trace(evaluater.rawCode);
                                trace(e.getStackTrace());
                                value = e.message;
                            }
                            
                            result += value;
                        }
                        else
                        {
                            result += theSegment;
                        }
                    }
                }
            }
            
            if (actualVariable != null)
            {
                s_vairableStack.pop();
            }
            
            return result;
        }
        
        private static function acquireEvaluater(code:String):Evaluater
        {
            var evaluter : Evaluater = s_cachedEvaluater[code];
            if (evaluter == null)
            {
                evaluter = new Evaluater(code);
                s_cachedEvaluater[code] = evaluter;
            }
            
            return evaluter;
        }
        
        private static function acquireTemplate(raw:String):Template
        {
            var template : Template = s_cachedTemplate[raw];
            if (template == null)
            {
                template = new Template(raw);
                s_cachedTemplate[raw] = template;
            }
            
            return template;
        }
        
        public static function init():Boolean
        {
            return BuildinFunc.init();
        }
    }
}