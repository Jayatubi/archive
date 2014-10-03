package expr
{
    
    public class BuildinFunc
    {
        public static function init():Boolean
        {
            Evaluater.registerFunc("Render", render);
            Evaluater.registerFunc("If", _if);
            Evaluater.registerFunc("PadLeft", padLeft);
            Evaluater.registerFunc("PadRight", padRight);
            Evaluater.registerFunc("Decimal", decimal);
            Evaluater.registerFunc("Floor", floor);
            Evaluater.registerFunc("Ceil", ceil);
            Evaluater.registerFunc("Round", round);
            Evaluater.registerFunc("Escape", escape);
            Evaluater.registerFunc("EscapeUnicode", escapeUnicode);
            Evaluater.registerFunc("Replace", replace);
            Evaluater.registerFunc("ReplaceWithCode", replaceWithCode);
            Evaluater.registerFunc("ToFixed", toFixed);
            
            Evaluater.registerFunc("Color", colorize);
            
            Evaluater.registerFunc("Red", function(value:*)
                {
                    return colorize(value, 0xFF0000);
                });
            Evaluater.registerFunc("Green", function(value:*)
                {
                    return colorize(value, 0x00FF00);
                });
            Evaluater.registerFunc("Blue", function(value:*)
                {
                    return colorize(value, 0x0000FF);
                });
            Evaluater.registerFunc("Yellow", function(value:*)
                {
                    return colorize(value, 0xFFFF00);
                });
            Evaluater.registerFunc("Purple", function(value:*)
                {
                    return colorize(value, 0xFF00FF);
                });
            Evaluater.registerFunc("Cyan", function(value:*)
                {
                    return colorize(value, 0x00FFFF);
                });
            Evaluater.registerFunc("Black", function(value:*)
                {
                    return colorize(value, 0x000000);
                });
            Evaluater.registerFunc("White", function(value:*)
                {
                    return colorize(value, 0xFFFFFF);
                });
            Evaluater.registerFunc("Gray", function(value:*)
                {
                    return colorize(value, 0x888888);
                });
            
            Evaluater.registerFunc("Orange", function(value:*)
                {
                    return colorize(value, 0xFF8800);
                });
            
            return true;
        }
        
        static private function colorize(value:*, color:*):String
        {
            var colorHex:String;
            
            if (color is String)
            {
                colorHex = color.toString();
            }
            if (color is uint || color is int)
            {
                colorHex = padLeft(((color >> 16) & 0xFF).toString(16), 2, '0') + padLeft(((color >> 8) & 0xFF).toString(16), 2, '0') + padLeft((color & 0xFF).toString(16), 2, '0');
            }
            
            return "<font color='#" + colorHex + "'>" + value + "</font>";
        }
        
        public static function render(template:String, variable:Object = null):String
        {
            return TextRenderer.render(template, variable);
        }
        
        public static function _if(cond:*, thenResult:* = null, elseResult:* = null):*
        {
            return Boolean(cond) ? thenResult : elseResult;
        }
        
        public static function padLeft(value:*, length:int, padding:String):String
        {
            var result:String = value != null ? value.toString() : "";
            while (result.length < length)
                result = padding + result;
            return result;
        }
        
        public static function padRight(value:*, length:int, padding:String):String
        {
            var result:String = value != null ? value.toString() : "";
            while (result.length < length)
                result = result + padding;
            return result;
        }
        
        public static function decimal(value:Number, digital:int):Number
        {
            var factor:int = Math.pow(10, digital);
            return Math.round(value * factor) / factor;
        }
        
        public static function floor(value:Number):Number
        {
            return Math.floor(value);
        }
        
        public static function toFixed(value:Number, decimals:uint):String
        {
            return value.toFixed(decimals);
        }
        
        public static function ceil(value:Number):Number
        {
            return Math.ceil(value);
        }
        
        public static function round(value:Number):Number
        {
            return Math.round(value);
        }
        
        public static function escape(value:String):String
        {
            var result:String = value;
            
            result = replace(result, "&", "&amp;");
            result = replace(result, "<", "&lt;");
            result = replace(result, ">", "&gt;");
            
            return result;
        }
        
        public static function escapeUnicode(value:String):String
        {
            var src:String = escape(value);
            
            var result:String = "";
            
            for (var i = 0; i < src.length; i++)
            {
                var charCode:int = src.charCodeAt(i);
                
                if (charCode < 32)
                {
                    //result += "&#x" + padLeft(charCode.toString(16), 4, "0") + ";";
                }
                else
                {
                    result += src.charAt(i);
                }
            }
            
            return result;
        }
        
        public static function replaceWithCode(src:String, code:Number, replacement:String):String
        {
            var pattern:String = String.fromCharCode(code);
            if (pattern != null)
            {
                return replace(src, pattern, replacement);
            }
            return "";
        }
        
        public static function replace(src:String, pattern:String, replacement:String):String
        {
            return src.split(pattern).join(replacement);
        }
    }
}