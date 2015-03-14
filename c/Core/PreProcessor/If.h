#ifndef GX_PREPROCESSOR_IF_H
#define GX_PREPROCESSOR_IF_H

#include "Bool.h"
#include "Cat.h"

#define PP_IIF_I_0(expr)
#define PP_IIF_I_1(expr) expr

#define PP_IIF(bit, expr) PP_CAT(PP_IIF_I_, bit)(expr) 
#define PP_IF(cond, expr) PP_IIF(PP_BOOL(cond), expr)

#define PP_COMMA ,

#define PP_COMMA_IF_0
#define PP_COMMA_IF_1 ,
#define PP_COMMA_IF_2 ,
#define PP_COMMA_IF_3 ,
#define PP_COMMA_IF_4 ,
#define PP_COMMA_IF_5 ,
#define PP_COMMA_IF_6 ,
#define PP_COMMA_IF_7 ,
#define PP_COMMA_IF_8 ,
#define PP_COMMA_IF_9 ,
#define PP_COMMA_IF_10 ,
#define PP_COMMA_IF_11 ,
#define PP_COMMA_IF_12 ,
#define PP_COMMA_IF_13 ,
#define PP_COMMA_IF_14 ,
#define PP_COMMA_IF_15 ,
#define PP_COMMA_IF_16 ,
#define PP_COMMA_IF_17 ,
#define PP_COMMA_IF_18 ,
#define PP_COMMA_IF_19 ,
#define PP_COMMA_IF_20 ,
#define PP_COMMA_IF_21 ,
#define PP_COMMA_IF_22 ,
#define PP_COMMA_IF_23 ,
#define PP_COMMA_IF_24 ,
#define PP_COMMA_IF_25 ,
#define PP_COMMA_IF_26 ,
#define PP_COMMA_IF_27 ,
#define PP_COMMA_IF_28 ,
#define PP_COMMA_IF_29 ,
#define PP_COMMA_IF_30 ,
#define PP_COMMA_IF_31 ,
#define PP_COMMA_IF_32 ,
#define PP_COMMA_IF_33 ,
#define PP_COMMA_IF_34 ,
#define PP_COMMA_IF_35 ,
#define PP_COMMA_IF_36 ,
#define PP_COMMA_IF_37 ,
#define PP_COMMA_IF_38 ,
#define PP_COMMA_IF_39 ,
#define PP_COMMA_IF_40 ,
#define PP_COMMA_IF_41 ,
#define PP_COMMA_IF_42 ,
#define PP_COMMA_IF_43 ,
#define PP_COMMA_IF_44 ,
#define PP_COMMA_IF_45 ,
#define PP_COMMA_IF_46 ,
#define PP_COMMA_IF_47 ,
#define PP_COMMA_IF_48 ,
#define PP_COMMA_IF_49 ,
#define PP_COMMA_IF_50 ,
#define PP_COMMA_IF_51 ,
#define PP_COMMA_IF_52 ,
#define PP_COMMA_IF_53 ,
#define PP_COMMA_IF_54 ,
#define PP_COMMA_IF_55 ,
#define PP_COMMA_IF_56 ,
#define PP_COMMA_IF_57 ,
#define PP_COMMA_IF_58 ,
#define PP_COMMA_IF_59 ,
#define PP_COMMA_IF_60 ,
#define PP_COMMA_IF_61 ,
#define PP_COMMA_IF_62 ,
#define PP_COMMA_IF_63 ,
#define PP_COMMA_IF_64 ,
#define PP_COMMA_IF_65 ,
#define PP_COMMA_IF_66 ,
#define PP_COMMA_IF_67 ,
#define PP_COMMA_IF_68 ,
#define PP_COMMA_IF_69 ,
#define PP_COMMA_IF_70 ,
#define PP_COMMA_IF_71 ,
#define PP_COMMA_IF_72 ,
#define PP_COMMA_IF_73 ,
#define PP_COMMA_IF_74 ,
#define PP_COMMA_IF_75 ,
#define PP_COMMA_IF_76 ,
#define PP_COMMA_IF_77 ,
#define PP_COMMA_IF_78 ,
#define PP_COMMA_IF_79 ,
#define PP_COMMA_IF_80 ,
#define PP_COMMA_IF_81 ,
#define PP_COMMA_IF_82 ,
#define PP_COMMA_IF_83 ,
#define PP_COMMA_IF_84 ,
#define PP_COMMA_IF_85 ,
#define PP_COMMA_IF_86 ,
#define PP_COMMA_IF_87 ,
#define PP_COMMA_IF_88 ,
#define PP_COMMA_IF_89 ,
#define PP_COMMA_IF_90 ,
#define PP_COMMA_IF_91 ,
#define PP_COMMA_IF_92 ,
#define PP_COMMA_IF_93 ,
#define PP_COMMA_IF_94 ,
#define PP_COMMA_IF_95 ,
#define PP_COMMA_IF_96 ,
#define PP_COMMA_IF_97 ,
#define PP_COMMA_IF_98 ,
#define PP_COMMA_IF_99 ,
#define PP_COMMA_IF_100 ,
#define PP_COMMA_IF_101 ,
#define PP_COMMA_IF_102 ,
#define PP_COMMA_IF_103 ,
#define PP_COMMA_IF_104 ,
#define PP_COMMA_IF_105 ,
#define PP_COMMA_IF_106 ,
#define PP_COMMA_IF_107 ,
#define PP_COMMA_IF_108 ,
#define PP_COMMA_IF_109 ,
#define PP_COMMA_IF_110 ,
#define PP_COMMA_IF_111 ,
#define PP_COMMA_IF_112 ,
#define PP_COMMA_IF_113 ,
#define PP_COMMA_IF_114 ,
#define PP_COMMA_IF_115 ,
#define PP_COMMA_IF_116 ,
#define PP_COMMA_IF_117 ,
#define PP_COMMA_IF_118 ,
#define PP_COMMA_IF_119 ,
#define PP_COMMA_IF_120 ,
#define PP_COMMA_IF_121 ,
#define PP_COMMA_IF_122 ,
#define PP_COMMA_IF_123 ,
#define PP_COMMA_IF_124 ,
#define PP_COMMA_IF_125 ,
#define PP_COMMA_IF_126 ,
#define PP_COMMA_IF_127 ,
#define PP_COMMA_IF_128 ,
#define PP_COMMA_IF_129 ,
#define PP_COMMA_IF_130 ,
#define PP_COMMA_IF_131 ,
#define PP_COMMA_IF_132 ,
#define PP_COMMA_IF_133 ,
#define PP_COMMA_IF_134 ,
#define PP_COMMA_IF_135 ,
#define PP_COMMA_IF_136 ,
#define PP_COMMA_IF_137 ,
#define PP_COMMA_IF_138 ,
#define PP_COMMA_IF_139 ,
#define PP_COMMA_IF_140 ,
#define PP_COMMA_IF_141 ,
#define PP_COMMA_IF_142 ,
#define PP_COMMA_IF_143 ,
#define PP_COMMA_IF_144 ,
#define PP_COMMA_IF_145 ,
#define PP_COMMA_IF_146 ,
#define PP_COMMA_IF_147 ,
#define PP_COMMA_IF_148 ,
#define PP_COMMA_IF_149 ,
#define PP_COMMA_IF_150 ,
#define PP_COMMA_IF_151 ,
#define PP_COMMA_IF_152 ,
#define PP_COMMA_IF_153 ,
#define PP_COMMA_IF_154 ,
#define PP_COMMA_IF_155 ,
#define PP_COMMA_IF_156 ,
#define PP_COMMA_IF_157 ,
#define PP_COMMA_IF_158 ,
#define PP_COMMA_IF_159 ,
#define PP_COMMA_IF_160 ,
#define PP_COMMA_IF_161 ,
#define PP_COMMA_IF_162 ,
#define PP_COMMA_IF_163 ,
#define PP_COMMA_IF_164 ,
#define PP_COMMA_IF_165 ,
#define PP_COMMA_IF_166 ,
#define PP_COMMA_IF_167 ,
#define PP_COMMA_IF_168 ,
#define PP_COMMA_IF_169 ,
#define PP_COMMA_IF_170 ,
#define PP_COMMA_IF_171 ,
#define PP_COMMA_IF_172 ,
#define PP_COMMA_IF_173 ,
#define PP_COMMA_IF_174 ,
#define PP_COMMA_IF_175 ,
#define PP_COMMA_IF_176 ,
#define PP_COMMA_IF_177 ,
#define PP_COMMA_IF_178 ,
#define PP_COMMA_IF_179 ,
#define PP_COMMA_IF_180 ,
#define PP_COMMA_IF_181 ,
#define PP_COMMA_IF_182 ,
#define PP_COMMA_IF_183 ,
#define PP_COMMA_IF_184 ,
#define PP_COMMA_IF_185 ,
#define PP_COMMA_IF_186 ,
#define PP_COMMA_IF_187 ,
#define PP_COMMA_IF_188 ,
#define PP_COMMA_IF_189 ,
#define PP_COMMA_IF_190 ,
#define PP_COMMA_IF_191 ,
#define PP_COMMA_IF_192 ,
#define PP_COMMA_IF_193 ,
#define PP_COMMA_IF_194 ,
#define PP_COMMA_IF_195 ,
#define PP_COMMA_IF_196 ,
#define PP_COMMA_IF_197 ,
#define PP_COMMA_IF_198 ,
#define PP_COMMA_IF_199 ,
#define PP_COMMA_IF_200 ,
#define PP_COMMA_IF_201 ,
#define PP_COMMA_IF_202 ,
#define PP_COMMA_IF_203 ,
#define PP_COMMA_IF_204 ,
#define PP_COMMA_IF_205 ,
#define PP_COMMA_IF_206 ,
#define PP_COMMA_IF_207 ,
#define PP_COMMA_IF_208 ,
#define PP_COMMA_IF_209 ,
#define PP_COMMA_IF_210 ,
#define PP_COMMA_IF_211 ,
#define PP_COMMA_IF_212 ,
#define PP_COMMA_IF_213 ,
#define PP_COMMA_IF_214 ,
#define PP_COMMA_IF_215 ,
#define PP_COMMA_IF_216 ,
#define PP_COMMA_IF_217 ,
#define PP_COMMA_IF_218 ,
#define PP_COMMA_IF_219 ,
#define PP_COMMA_IF_220 ,
#define PP_COMMA_IF_221 ,
#define PP_COMMA_IF_222 ,
#define PP_COMMA_IF_223 ,
#define PP_COMMA_IF_224 ,
#define PP_COMMA_IF_225 ,
#define PP_COMMA_IF_226 ,
#define PP_COMMA_IF_227 ,
#define PP_COMMA_IF_228 ,
#define PP_COMMA_IF_229 ,
#define PP_COMMA_IF_230 ,
#define PP_COMMA_IF_231 ,
#define PP_COMMA_IF_232 ,
#define PP_COMMA_IF_233 ,
#define PP_COMMA_IF_234 ,
#define PP_COMMA_IF_235 ,
#define PP_COMMA_IF_236 ,
#define PP_COMMA_IF_237 ,
#define PP_COMMA_IF_238 ,
#define PP_COMMA_IF_239 ,
#define PP_COMMA_IF_240 ,
#define PP_COMMA_IF_241 ,
#define PP_COMMA_IF_242 ,
#define PP_COMMA_IF_243 ,
#define PP_COMMA_IF_244 ,
#define PP_COMMA_IF_245 ,
#define PP_COMMA_IF_246 ,
#define PP_COMMA_IF_247 ,
#define PP_COMMA_IF_248 ,
#define PP_COMMA_IF_249 ,
#define PP_COMMA_IF_250 ,
#define PP_COMMA_IF_251 ,
#define PP_COMMA_IF_252 ,
#define PP_COMMA_IF_253 ,
#define PP_COMMA_IF_254 ,
#define PP_COMMA_IF_255 ,
#define PP_COMMA_IF_256 ,

#define PP_COMMA_IF(n) PP_CAT(PP_COMMA_IF_, n)

#endif