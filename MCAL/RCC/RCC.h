/*
 * RCC.h
 *
 *  Created on: Jan 31, 2023
 *      Author: lenovo
 */

#ifndef RCC_H_
#define RCC_H_

#include "Std_types.h"
#include "Bit_math.h"

/***************************************************************************************************/
/******************************************** DEFINES **********************************************/

/* for prescalers of AHB bus */
#define RCC_PRESCALER_AHB_1 0x00000100
#define RCC_PRESCALER_AHB_2 0x00000180
#define RCC_PRESCALER_AHB_4 0x00000190
#define RCC_PRESCALER_AHB_8 0x000001A0
#define RCC_PRESCALER_AHB_16 0x000001B0
#define RCC_PRESCALER_AHB_64 0x000001C0
#define RCC_PRESCALER_AHB_128 0x000001D0
#define RCC_PRESCALER_AHB_256 0x000001E0
#define RCC_PRESCALER_AHB_512 0x000001F0

/* for prescalers of APB1 bus */
#define RCC_PRESCALER_APB1_1 0x00000200
#define RCC_PRESCALER_APB1_2 0x00001200
#define RCC_PRESCALER_APB1_4 0x00001600
#define RCC_PRESCALER_APB1_8 0x00001A00
#define RCC_PRESCALER_APB1_16 0x00001E00

/* for prescalers of APB2 bus */
#define RCC_PRESCALER_APB2_1 0x00000300
#define RCC_PRESCALER_APB2_2 0x00008300
#define RCC_PRESCALER_APB2_4 0x0000A300
#define RCC_PRESCALER_APB2_8 0x0000C300
#define RCC_PRESCALER_APB2_16 0x0000E300

/* for PLL configuration : m division factor */
#define RCC_VALUE_PLLM_2  2
#define RCC_VALUE_PLLM_3  3
#define RCC_VALUE_PLLM_4  4
#define RCC_VALUE_PLLM_5  5
#define RCC_VALUE_PLLM_6  6
#define RCC_VALUE_PLLM_7  7
#define RCC_VALUE_PLLM_8  8
#define RCC_VALUE_PLLM_9  9
#define RCC_VALUE_PLLM_10 10
#define RCC_VALUE_PLLM_11 11
#define RCC_VALUE_PLLM_12 12
#define RCC_VALUE_PLLM_13 13
#define RCC_VALUE_PLLM_14 14
#define RCC_VALUE_PLLM_15 15
#define RCC_VALUE_PLLM_16 16
#define RCC_VALUE_PLLM_17 17
#define RCC_VALUE_PLLM_18 18
#define RCC_VALUE_PLLM_19 19
#define RCC_VALUE_PLLM_20 20
#define RCC_VALUE_PLLM_21 21
#define RCC_VALUE_PLLM_22 22
#define RCC_VALUE_PLLM_23 23
#define RCC_VALUE_PLLM_24 24
#define RCC_VALUE_PLLM_25 25
#define RCC_VALUE_PLLM_26 26
#define RCC_VALUE_PLLM_27 27
#define RCC_VALUE_PLLM_28 28
#define RCC_VALUE_PLLM_29 29
#define RCC_VALUE_PLLM_30 30
#define RCC_VALUE_PLLM_31 31
#define RCC_VALUE_PLLM_32 32
#define RCC_VALUE_PLLM_33 33
#define RCC_VALUE_PLLM_34 34
#define RCC_VALUE_PLLM_35 35
#define RCC_VALUE_PLLM_36 36

/* for PLL configuration : n multiplication factor */
#define RCC_VALUE_PLLN_192 192
#define RCC_VALUE_PLLN_193 193
#define RCC_VALUE_PLLN_194 194
#define RCC_VALUE_PLLN_195 195
#define RCC_VALUE_PLLN_196 196
#define RCC_VALUE_PLLN_197 197
#define RCC_VALUE_PLLN_198 198
#define RCC_VALUE_PLLN_199 199
#define RCC_VALUE_PLLN_200 200
#define RCC_VALUE_PLLN_201 201
#define RCC_VALUE_PLLN_202 202
#define RCC_VALUE_PLLN_203 203
#define RCC_VALUE_PLLN_204 204
#define RCC_VALUE_PLLN_205 205
#define RCC_VALUE_PLLN_206 206
#define RCC_VALUE_PLLN_207 207
#define RCC_VALUE_PLLN_208 208
#define RCC_VALUE_PLLN_209 209
#define RCC_VALUE_PLLN_210 210
#define RCC_VALUE_PLLN_211 211
#define RCC_VALUE_PLLN_212 212
#define RCC_VALUE_PLLN_213 213
#define RCC_VALUE_PLLN_214 214
#define RCC_VALUE_PLLN_215 215
#define RCC_VALUE_PLLN_216 216
#define RCC_VALUE_PLLN_217 217
#define RCC_VALUE_PLLN_218 218
#define RCC_VALUE_PLLN_219 219
#define RCC_VALUE_PLLN_220 220
#define RCC_VALUE_PLLN_221 221
#define RCC_VALUE_PLLN_222 222
#define RCC_VALUE_PLLN_223 223
#define RCC_VALUE_PLLN_224 224
#define RCC_VALUE_PLLN_225 225
#define RCC_VALUE_PLLN_226 226
#define RCC_VALUE_PLLN_227 227
#define RCC_VALUE_PLLN_228 228
#define RCC_VALUE_PLLN_229 229
#define RCC_VALUE_PLLN_230 230
#define RCC_VALUE_PLLN_231 231
#define RCC_VALUE_PLLN_232 232
#define RCC_VALUE_PLLN_233 233
#define RCC_VALUE_PLLN_234 234
#define RCC_VALUE_PLLN_235 235
#define RCC_VALUE_PLLN_236 236
#define RCC_VALUE_PLLN_237 237
#define RCC_VALUE_PLLN_238 238
#define RCC_VALUE_PLLN_239 239
#define RCC_VALUE_PLLN_240 240
#define RCC_VALUE_PLLN_241 241
#define RCC_VALUE_PLLN_242 242
#define RCC_VALUE_PLLN_243 243
#define RCC_VALUE_PLLN_244 244
#define RCC_VALUE_PLLN_245 245
#define RCC_VALUE_PLLN_246 246
#define RCC_VALUE_PLLN_247 247
#define RCC_VALUE_PLLN_248 248
#define RCC_VALUE_PLLN_249 249
#define RCC_VALUE_PLLN_250 250
#define RCC_VALUE_PLLN_251 251
#define RCC_VALUE_PLLN_252 252
#define RCC_VALUE_PLLN_253 253
#define RCC_VALUE_PLLN_254 254
#define RCC_VALUE_PLLN_255 255
#define RCC_VALUE_PLLN_256 256
#define RCC_VALUE_PLLN_257 257
#define RCC_VALUE_PLLN_258 258
#define RCC_VALUE_PLLN_259 259
#define RCC_VALUE_PLLN_260 260
#define RCC_VALUE_PLLN_261 261
#define RCC_VALUE_PLLN_262 262
#define RCC_VALUE_PLLN_263 263
#define RCC_VALUE_PLLN_264 264
#define RCC_VALUE_PLLN_265 265
#define RCC_VALUE_PLLN_266 266
#define RCC_VALUE_PLLN_267 267
#define RCC_VALUE_PLLN_268 268
#define RCC_VALUE_PLLN_269 269
#define RCC_VALUE_PLLN_270 270
#define RCC_VALUE_PLLN_271 271
#define RCC_VALUE_PLLN_272 272
#define RCC_VALUE_PLLN_273 273
#define RCC_VALUE_PLLN_274 274
#define RCC_VALUE_PLLN_275 275
#define RCC_VALUE_PLLN_276 276
#define RCC_VALUE_PLLN_277 277
#define RCC_VALUE_PLLN_278 278
#define RCC_VALUE_PLLN_279 279
#define RCC_VALUE_PLLN_280 280
#define RCC_VALUE_PLLN_281 281
#define RCC_VALUE_PLLN_282 282
#define RCC_VALUE_PLLN_283 283
#define RCC_VALUE_PLLN_284 284
#define RCC_VALUE_PLLN_285 285
#define RCC_VALUE_PLLN_286 286
#define RCC_VALUE_PLLN_287 287
#define RCC_VALUE_PLLN_288 288
#define RCC_VALUE_PLLN_289 289
#define RCC_VALUE_PLLN_290 290
#define RCC_VALUE_PLLN_291 291
#define RCC_VALUE_PLLN_292 292
#define RCC_VALUE_PLLN_293 293
#define RCC_VALUE_PLLN_294 294
#define RCC_VALUE_PLLN_295 295
#define RCC_VALUE_PLLN_296 296
#define RCC_VALUE_PLLN_297 297
#define RCC_VALUE_PLLN_298 298
#define RCC_VALUE_PLLN_299 299
#define RCC_VALUE_PLLN_300 300
#define RCC_VALUE_PLLN_301 301
#define RCC_VALUE_PLLN_302 302
#define RCC_VALUE_PLLN_303 303
#define RCC_VALUE_PLLN_304 304
#define RCC_VALUE_PLLN_305 305
#define RCC_VALUE_PLLN_306 306
#define RCC_VALUE_PLLN_307 307
#define RCC_VALUE_PLLN_308 308
#define RCC_VALUE_PLLN_309 309
#define RCC_VALUE_PLLN_310 310
#define RCC_VALUE_PLLN_311 311
#define RCC_VALUE_PLLN_312 312
#define RCC_VALUE_PLLN_313 313
#define RCC_VALUE_PLLN_314 314
#define RCC_VALUE_PLLN_315 315
#define RCC_VALUE_PLLN_316 316
#define RCC_VALUE_PLLN_317 317
#define RCC_VALUE_PLLN_318 318
#define RCC_VALUE_PLLN_319 319
#define RCC_VALUE_PLLN_320 320
#define RCC_VALUE_PLLN_321 321
#define RCC_VALUE_PLLN_322 322
#define RCC_VALUE_PLLN_323 323
#define RCC_VALUE_PLLN_324 324
#define RCC_VALUE_PLLN_325 325
#define RCC_VALUE_PLLN_326 326
#define RCC_VALUE_PLLN_327 327
#define RCC_VALUE_PLLN_328 328
#define RCC_VALUE_PLLN_329 329
#define RCC_VALUE_PLLN_330 330
#define RCC_VALUE_PLLN_331 331
#define RCC_VALUE_PLLN_332 332
#define RCC_VALUE_PLLN_333 333
#define RCC_VALUE_PLLN_334 334
#define RCC_VALUE_PLLN_335 335
#define RCC_VALUE_PLLN_336 336
#define RCC_VALUE_PLLN_337 337
#define RCC_VALUE_PLLN_338 338
#define RCC_VALUE_PLLN_339 339
#define RCC_VALUE_PLLN_340 340
#define RCC_VALUE_PLLN_341 341
#define RCC_VALUE_PLLN_342 342
#define RCC_VALUE_PLLN_343 343
#define RCC_VALUE_PLLN_344 344
#define RCC_VALUE_PLLN_345 345
#define RCC_VALUE_PLLN_346 346
#define RCC_VALUE_PLLN_347 347
#define RCC_VALUE_PLLN_348 348
#define RCC_VALUE_PLLN_349 349
#define RCC_VALUE_PLLN_350 350
#define RCC_VALUE_PLLN_351 351
#define RCC_VALUE_PLLN_352 352
#define RCC_VALUE_PLLN_353 353
#define RCC_VALUE_PLLN_354 354
#define RCC_VALUE_PLLN_355 355
#define RCC_VALUE_PLLN_356 356
#define RCC_VALUE_PLLN_357 357
#define RCC_VALUE_PLLN_358 358
#define RCC_VALUE_PLLN_359 359
#define RCC_VALUE_PLLN_360 360
#define RCC_VALUE_PLLN_361 361
#define RCC_VALUE_PLLN_362 362
#define RCC_VALUE_PLLN_363 363
#define RCC_VALUE_PLLN_364 364
#define RCC_VALUE_PLLN_365 365
#define RCC_VALUE_PLLN_366 366
#define RCC_VALUE_PLLN_367 367
#define RCC_VALUE_PLLN_368 368
#define RCC_VALUE_PLLN_369 369
#define RCC_VALUE_PLLN_370 370
#define RCC_VALUE_PLLN_371 371
#define RCC_VALUE_PLLN_372 372
#define RCC_VALUE_PLLN_373 373
#define RCC_VALUE_PLLN_374 374
#define RCC_VALUE_PLLN_375 375
#define RCC_VALUE_PLLN_376 376
#define RCC_VALUE_PLLN_377 377
#define RCC_VALUE_PLLN_378 378
#define RCC_VALUE_PLLN_379 379
#define RCC_VALUE_PLLN_380 380
#define RCC_VALUE_PLLN_381 381
#define RCC_VALUE_PLLN_382 382
#define RCC_VALUE_PLLN_383 383
#define RCC_VALUE_PLLN_384 384
#define RCC_VALUE_PLLN_385 385
#define RCC_VALUE_PLLN_386 386
#define RCC_VALUE_PLLN_387 387
#define RCC_VALUE_PLLN_388 388
#define RCC_VALUE_PLLN_389 389
#define RCC_VALUE_PLLN_390 390
#define RCC_VALUE_PLLN_391 391
#define RCC_VALUE_PLLN_392 392
#define RCC_VALUE_PLLN_393 393
#define RCC_VALUE_PLLN_394 394
#define RCC_VALUE_PLLN_395 395
#define RCC_VALUE_PLLN_396 396
#define RCC_VALUE_PLLN_397 397
#define RCC_VALUE_PLLN_398 398
#define RCC_VALUE_PLLN_399 399
#define RCC_VALUE_PLLN_400 400
#define RCC_VALUE_PLLN_401 401
#define RCC_VALUE_PLLN_402 402
#define RCC_VALUE_PLLN_403 403
#define RCC_VALUE_PLLN_404 404
#define RCC_VALUE_PLLN_405 405
#define RCC_VALUE_PLLN_406 406
#define RCC_VALUE_PLLN_407 407
#define RCC_VALUE_PLLN_408 408
#define RCC_VALUE_PLLN_409 409
#define RCC_VALUE_PLLN_410 410
#define RCC_VALUE_PLLN_411 411
#define RCC_VALUE_PLLN_412 412
#define RCC_VALUE_PLLN_413 413
#define RCC_VALUE_PLLN_414 414
#define RCC_VALUE_PLLN_415 415
#define RCC_VALUE_PLLN_416 416
#define RCC_VALUE_PLLN_417 417
#define RCC_VALUE_PLLN_418 418
#define RCC_VALUE_PLLN_419 419
#define RCC_VALUE_PLLN_420 420
#define RCC_VALUE_PLLN_421 421
#define RCC_VALUE_PLLN_422 422
#define RCC_VALUE_PLLN_423 423
#define RCC_VALUE_PLLN_424 424
#define RCC_VALUE_PLLN_425 425
#define RCC_VALUE_PLLN_426 426
#define RCC_VALUE_PLLN_427 427
#define RCC_VALUE_PLLN_428 428
#define RCC_VALUE_PLLN_429 429
#define RCC_VALUE_PLLN_430 430
#define RCC_VALUE_PLLN_431 431
#define RCC_VALUE_PLLN_432 432

/* for PLL configuration : Q division factor*/
#define RCC_VALUE_PLLQ_2  2
#define RCC_VALUE_PLLQ_3  3
#define RCC_VALUE_PLLQ_4  4
#define RCC_VALUE_PLLQ_5  5
#define RCC_VALUE_PLLQ_6  6
#define RCC_VALUE_PLLQ_7  7
#define RCC_VALUE_PLLQ_8  8
#define RCC_VALUE_PLLQ_9  9
#define RCC_VALUE_PLLQ_10 10
#define RCC_VALUE_PLLQ_11 11
#define RCC_VALUE_PLLQ_12 12
#define RCC_VALUE_PLLQ_13 13
#define RCC_VALUE_PLLQ_14 14
#define RCC_VALUE_PLLQ_15 15

/***************************************************************************************************/
/********************************************* TYPES ***********************************************/

typedef enum
{
	RCC_enuOK = 0,
	RCC_enuNotOk,
	Rcc_enuNullPointer
}RCC_tenuErrorStatus;

typedef enum
{
	RCC_enuHSIoscillator = 0 ,
	RCC_enuHSEoscillator,
	RCC_enuPLL,
	RCC_enuNotApplicaple
}RCC_tenuSystemClk;

typedef enum
{
	RCC_enuValuePLLP_2 = 0,
	RCC_enuValuePLLP_4,
	RCC_enuValuePLLP_6,
	RCC_enuValuePLLP_8
}RCC_tenuValuePLLP;

typedef enum
{
	/* AHB1 peripherals */
	RCC_enuPeripheralGPIOA = 0,
	RCC_enuPeripheralGPIOB,
	RCC_enuPeripheralGPIOC,
	RCC_enuPeripheralGPIOD,
	RCC_enuPeripheralGPIOE,
	RCC_enuPeripheralGPIOH,
	RCC_enuPeripheralCRC,
	RCC_enuPeripheralDMA1,
	RCC_enuPeripheralDMA2,

	/* AHB2 peripherals */
	RCC_enuPeripheralOTGFS,

	/* APB1 peripherals */
	RCC_enuPeripheralTIM2,
	RCC_enuPeripheralTIM3,
	RCC_enuPeripheralTIM4,
	RCC_enuPeripheralTIM5,
	RCC_enuPeripheralWWDG,
	RCC_enuPeripheralSPI2,
	RCC_enuPeripheralSPI3,
	RCC_enuPeripheralUSART2,
	RCC_enuPeripheralI2C1,
	RCC_enuPeripheralI2C2,
	RCC_enuPeripheralI2C3,
	RCC_enuPeripheralPWP,

	/* APB2 peripherals */
	RCC_enuPeripheralTIM1,
	RCC_enuPeripheralUSART1,
	RCC_enuPeripheralUSART6,
	RCC_enuPeripheralADC1,
	RCC_enuPeripheralSDIO,
	RCC_enuPeripheralSPI1,
	RCC_enuPeripheralSPI4,
	RCC_enuPeripheralSYSCFG,
	RCC_enuPeripheralTIM9,
	RCC_enuPeripheralTIM10,
	RCC_enuPeripheralTIM11,

	RCC_enuPeripheralNumber
}RCC_tenuPeripherals;

typedef enum
{
	RCC_enuEnable = 0,
	RCC_enuDisable
}RCC_tenuPeripheralStatus;

/***************************************************************************************************/
/************************************** FUNCTIONS APIS *********************************************/

/*****************************************************
 * To get the currently used clock for the system    *
 * input : pointer to get the current system clk     *
 * return : Error status                             *
 * ***************************************************/
RCC_tenuErrorStatus RCC_enuGetSystemClk(RCC_tenuSystemClk * Add_PenuSystemClk);


/*****************************************************
 * To enable HSI oscillator                          *
 * input : void                                      *
 * return : Error status                             *
 * ***************************************************/
RCC_tenuErrorStatus RCC_enuEnableHSI(void);


/*****************************************************
 * To disable HSI oscillator                         *
 * input : void                                      *
 * return : Error status                             *
 * ***************************************************/
RCC_tenuErrorStatus RCC_enuDisableHSI(void);


/*****************************************************
 * To enable HSE oscillator                          *
 * input : void                                      *
 * return : Error status                             *
 * ***************************************************/
RCC_tenuErrorStatus RCC_enuEnableHSE(void);


/*****************************************************
 * To disable HSE oscillator                         *
 * input : void                                      *
 * return : Error status                             *
 * ***************************************************/
RCC_tenuErrorStatus RCC_enuDisableHSE(void);


/*****************************************************
 * To enable PLL oscillator                          *
 * input : void                                      *
 * return : Error status                             *
 * ***************************************************/
RCC_tenuErrorStatus RCC_enuEnablePLL(void);


/*****************************************************
 * To disable PLL oscillator                         *
 * input : void                                      *
 * return : Error status                             *
 * ***************************************************/
RCC_tenuErrorStatus RCC_enuDisablePLL(void);


/*******************************************************************************
 * To configure PLL                                                            *
 * input : PLL source (RCC_enuHSIoscillator, RCC_enuHSEoscillator )            *
 *         m division factor (RCC_VALUE_PLLM_X where X from 2 to 36 )          *
 *         n multiplication factor (RCC_VALUE_PLLN_X where X from 192 to 432 ) *
 *         p division factor (RCC_enuValuePLLP_X where X= 2,4,6,8 )            *
 *         q division factor (RCC_VALUE_PLLQ_X where X from 2 to 15 )          *
 * return : Error status                                                       *
 * *****************************************************************************/
RCC_tenuErrorStatus RCC_enuConfigurationPLL(RCC_tenuSystemClk Cpy_enuPLLsource, u8 Cpy_u8DivFacMainPll_M, u16 Cpy_u16MulFacVCO_N, RCC_tenuValuePLLP Cpy_u8DivFacMainSys_P, u8 Cpy_u8DivFacUSB_Q);


/*******************************************************************************
 * To set the system clk                                                       *
 * input : system clk (RCC_enuHSIoscillator, RCC_enuHSEoscillator, RCC_enuPLL )*
 * return : Error status                                                       *
 * *****************************************************************************/
RCC_tenuErrorStatus RCC_enuSetSystemClk (RCC_tenuSystemClk Cpy_enuSystemClk);


/*******************************************************************************
 * To check if the chosen clock is ready                                       *
 * input : system clk (RCC_enuHSIoscillator, RCC_enuHSEoscillator, RCC_enuPLL )*
 * return : Error status                                                       *
 * *****************************************************************************/
RCC_tenuErrorStatus RCC_enuCheckClkStatus (RCC_tenuSystemClk Cpy_enuSystemClk);


/*******************************************************************************
 * To enable clk for certain peripheral                                        *
 * input : peripheral (RCC_enuPeripheralX )                                    *
 *         peripheral status ( RCC_enuEnable , RCC_enuDisable )                *
 * return : Error status                                                       *
 * *****************************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk (RCC_tenuPeripherals Cpy_enuPeripheral, RCC_tenuPeripheralStatus Cpy_enuPeripheralStatus);


/**************************************************************************************
 * To set the clk division factor for AHB                                             *
 * input : prescaler (RCC_PRESCALER_AHB_X where X = 1, 2, 4, 8, 16, 64, 128, 256, 512 *
 * return : Error status                                                              *
 * ************************************************************************************/
RCC_tenuErrorStatus RCC_enuSetPrescalerAHB (u32 Cpy_u8PrescalerAHB);


/**************************************************************************************
 * To set the clk division factor for APB1                                            *
 * input : prescaler (RCC_PRESCALER_APB1_X where X = 1, 2, 4, 8, 16)                  *
 * return : Error status                                                              *
 * ************************************************************************************/
RCC_tenuErrorStatus RCC_enuSetPrescalerAPB1 (u32 Cpy_u8PrescalerAPB1);


/**************************************************************************************
 * To set the clk division factor for APB2                                            *
 * input : prescaler (RCC_PRESCALER_APB2_X where X = 1, 2, 4, 8, 16)                  *
 * return : Error status                                                              *
 * ************************************************************************************/
RCC_tenuErrorStatus RCC_enuSetPrescalerAPB2 (u32 Cpy_u8PrescalerAPB2);


#endif /* RCC_H_ */
