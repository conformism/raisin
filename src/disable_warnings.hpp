#ifndef DISABLE_WARNINGS_HPP
#define DISABLE_WARNINGS_HPP

/// @def   DISABLE_WARNINGS
/// @brief Use this to disable -Wall and -Wextra
///*****************************************************************************
#define DISABLE_WARNINGS \
	_Pragma("GCC diagnostic push") \
\
		_Pragma("GCC diagnostic ignored \"-Wunknown-pragmas\"") _Pragma( \
			"GCC diagnostic ignored \"-Wpragmas\"") \
\
			_Pragma("GCC diagnostic ignored \"-Waddress\"") _Pragma( \
				"GCC diagnostic ignored \"-Warray-bounds=1\"") \
				_Pragma("GCC diagnostic ignored \"-Wbool-compare\"") _Pragma( \
					"GCC diagnostic ignored \"-Wbool-operation\"") \
					_Pragma("GCC diagnostic ignored \"-Wc++11-compat\"") _Pragma( \
						"GCC diagnostic ignored \"-Wcatch-value\"") \
						_Pragma("GCC diagnostic ignored \"-Wchar-subscripts\"") _Pragma( \
							"GCC diagnostic ignored \"-Wcomment\"") \
							_Pragma("GCC diagnostic ignored \"-Wenum-compare\"") _Pragma( \
								"GCC diagnostic ignored \"-Wenum-conversion\"") \
								_Pragma("GCC diagnostic ignored \"-Wformat\"") _Pragma( \
									"GCC diagnostic ignored \"-Wformat-overflow\"") \
									_Pragma("GCC diagnostic ignored \"-Wformat-truncation\"") _Pragma( \
										"GCC diagnostic ignored \"-Wint-in-bool-context\"") \
										_Pragma("GCC diagnostic ignored \"-Winit-self\"") _Pragma( \
											"GCC diagnostic ignored " \
											"\"-Wlogical-not-parentheses\"") \
											_Pragma("GCC diagnostic ignored \"-Wmain\"") _Pragma( \
												"GCC diagnostic ignored " \
												"\"-Wmaybe-uninitialized\"") \
												_Pragma( \
													"GCC diagnostic ignored " \
													"\"-Wmemset-elt-size\"") \
													_Pragma( \
														"GCC diagnostic ignored " \
														"\"-Wmemset-transposed-args\"") \
														_Pragma( \
															"GCC diagnostic ignored " \
															"\"-Wmisleading-indentation\"") \
															_Pragma( \
																"GCC diagnostic ignored " \
																"\"-Wmissing-attributes\"") \
																_Pragma( \
																	"GCC diagnostic ignored " \
																	"\"-Wmissing-braces\"") \
																	_Pragma( \
																		"GCC diagnostic ignored " \
																		"\"-Wmultistatement-" \
																		"macros\"") \
																		_Pragma( \
																			"GCC diagnostic " \
																			"ignored " \
																			"\"-Wnarrowing\"") \
																			_Pragma( \
																				"GCC diagnostic " \
																				"ignored " \
																				"\"-Wnonnull\"") \
																				_Pragma( \
																					"GCC " \
																					"diagnostic " \
																					"ignored " \
																					"\"-Wnonnull-" \
																					"compare\"") \
																					_Pragma( \
																						"GCC " \
																						"diagnost" \
																						"ic " \
																						"ignored " \
																						"\"-" \
																						"Wopenmp-" \
																						"simd\"") \
																						_Pragma( \
																							"GCC " \
																							"diag" \
																							"nost" \
																							"ic " \
																							"igno" \
																							"red " \
																							"\"-" \
																							"Wpar" \
																							"enth" \
																							"eses" \
																							"\"") \
																							_Pragma( \
																								"GCC diagnostic ignored \"-Wpessimizing-move\"") \
																								_Pragma( \
																									"GCC diagnostic ignored \"-Wreorder\"") \
																									_Pragma( \
																										"GCC diagnostic ignored \"-Wrestrict\"") \
																										_Pragma( \
																											"GCC diagnostic ignored \"-Wreturn-type\"") \
																											_Pragma( \
																												"GCC diagnostic ignored \"-Wsequence-point\"") \
																												_Pragma( \
																													"GCC diagnostic ignored \"-Wsign-compare\"") \
																													_Pragma( \
																														"GCC diagnostic ignored \"-Wsizeof-pointer-div\"") \
																														_Pragma( \
																															"GCC diagnostic ignored \"-Wsizeof-pointer-memaccess\"") \
																															_Pragma( \
																																"GCC diagnostic ignored \"-Wstrict-aliasing\"") \
																																_Pragma( \
																																	"GCC diagnostic ignored \"-Wstrict-overflow=1\"") \
																																	_Pragma( \
																																		"GCC diagnostic ignored \"-Wswitch\"") \
																																		_Pragma( \
																																			"GCC diagnostic ignored \"-Wtautological-compare\"") \
																																			_Pragma( \
																																				"GCC diagnostic ignored \"-Wtrigraphs\"") \
																																				_Pragma( \
																																					"GCC diagnostic ignored \"-Wuninitialized\"") \
																																					_Pragma( \
																																						"GCC diagnostic ignored \"-Wunknown-pragmas\"") \
																																						_Pragma( \
																																							"GCC diagnostic ignored \"-Wunused-function\"") \
																																							_Pragma( \
																																								"GCC diagnostic ignored \"-Wunused-label\"") \
																																								_Pragma( \
																																									"GCC diagnostic ignored \"-Wunused-value\"") \
																																									_Pragma( \
																																										"GCC diagnostic ignored \"-Wunused-variable\"") \
																																										_Pragma( \
																																											"GCC diagnostic ignored \"-Wvolatile-register-var\"") \
\
																																											_Pragma( \
																																												"GCC diagnostic ignored \"-Wclobbered\"") \
																																												_Pragma( \
																																													"GCC diagnostic ignored \"-Wcast-function-type\"") \
																																													_Pragma( \
																																														"GCC diagnostic ignored \"-Wdeprecated-copy\"") \
																																														_Pragma( \
																																															"GCC diagnostic ignored \"-Wempty-body\"") \
																																															_Pragma( \
																																																"GCC diagnostic ignored \"-Wignored-qualifiers\"") \
																																																_Pragma( \
																																																	"GCC diagnostic ignored \"-Wimplicit-fallthrough=3\"") \
																																																	_Pragma( \
																																																		"GCC diagnostic ignored \"-Wmissing-field-initializers\"") \
																																																		_Pragma( \
																																																			"GCC diagnostic ignored \"-Wsign-compare\"") \
																																																			_Pragma( \
																																																				"GCC diagnostic ignored \"-Wstring-compare\"") \
																																																				_Pragma( \
																																																					"GCC diagnostic ignored \"-Wredundant-move\"") \
																																																					_Pragma( \
																																																						"GCC diagnostic ignored \"-Wtype-limits\"") \
																																																						_Pragma( \
																																																							"GCC diagnostic ignored \"-Wuninitialized\"") \
																																																							_Pragma( \
																																																								"GCC diagnostic ignored \"-Wshift-negative-value\"") \
																																																								_Pragma( \
																																																									"GCC diagnostic ignored \"-Wunused-parameter\"") \
																																																									_Pragma( \
																																																										"GCC diagnostic ignored \"-Wunused-but-set-parameter\"")

/// @def   REENABLE_WARNINGS
/// @brief Use this to reset the previous -W settings
///*****************************************************************************
#define REENABLE_WARNINGS _Pragma("GCC diagnostic pop")

#endif  // DISABLE_WARNINGS_HPP
