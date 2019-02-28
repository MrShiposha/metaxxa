#ifndef METAXXA_detail_TYPEHASOPERATORMETHODMACROS_H
#define METAXXA_detail_TYPEHASOPERATORMETHODMACROS_H

#define ___METAXXA___TYPE___DECLARE_UNARY_OPERATOR(OPERATOR) \
	template <typename Callable> 							 \
	static constexpr bool has_operator_##OPERATOR(); 		 \
															 \
	static constexpr bool has_single_operator_##OPERATOR();

#define ___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(OPERATOR) \
	template <typename Callable> 			   			      \
	static constexpr bool has_operator_##OPERATOR();	      \
															  \
	static constexpr bool has_single_operator_##OPERATOR();

#define ___METAXXA___TYPE___DECLARE_UNARY_AND_BINARY_OPERATOR(OPERATOR) \
	template <typename Callable> 										\
	static constexpr bool has_operator_##OPERATOR();		   		    \
																	    \
	static constexpr bool has_single_operator_unary_##OPERATOR();		\
																		\
	static constexpr bool has_single_operator_binary_##OPERATOR();

#define ___METAXXA___TYPE___DECLARE_NAMED_UNARY_AND_BINARY_OPERATOR(OPERATOR, UNARY_NAME, BINARY_NAME) \
	template <typename Callable> 										   \
	static constexpr bool has_operator_##UNARY_NAME();					   \
																		   \
	static constexpr bool has_single_operator_##OPERATOR##_##UNARY_NAME(); \
																		   \
	template <typename Callable> 										   \
	static constexpr bool has_operator_##BINARY_NAME();					   \
																	       \
	static constexpr bool has_single_operator_##OPERATOR##_##BINARY_NAME();


#define ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR(OPERATOR) \
	template <typename SomeType>														   			   \
	template <typename Callable> 													       			   \
	constexpr bool Type<SomeType>::has_operator_##OPERATOR() 							   			   \
	{ 																					   			   \
		return metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, Callable>::has();    \
	} 																					   			   \
																						   			   \
	template <typename SomeType>														   			   \
	constexpr bool Type<SomeType>::has_single_operator_##OPERATOR() 					   			   \
	{ 																					   			   \
		return metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, void>::has(); 	   \
	} 

#define ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(OPERATOR) \
	template <typename SomeType>														   			   \
	template <typename Callable> 														   			   \
	constexpr bool Type<SomeType>::has_operator_##OPERATOR() 							   			   \
	{ 																					   			   \
		return metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, Callable>::has();    \
	} 																					   			   \
																						   			   \
	template <typename SomeType>														   			   \
	constexpr bool Type<SomeType>::has_single_operator_##OPERATOR() 					   			   \
	{ 																					   			   \
		return metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, void>::has(); 	   \
	} 

#define ___METAXXA___TYPE___DEFINE_UNARY_AND_BINARY_OPERATOR(OPERATOR) \
	template <typename SomeType>														   																										   \
	template <typename Callable> 														   																										   \
	constexpr bool Type<SomeType>::has_operator_##OPERATOR() 							   																										   \
	{ 																					   																										   \
		return metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, Callable>::has(); 																							   \
	} 																					   																										   \
	template <typename SomeType>														   																										   \
	constexpr bool Type<SomeType>::has_single_operator_unary_##OPERATOR() 				   																										   \
	{ 																					   																										   \
		return metaxxa::detail::___METAXXA___POSTCONDITION_OPERATOR_CHECKER_unary_##OPERATOR<SomeType, metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, void>::has()>::check();  \
	} 																					   																										   \
	template <typename SomeType>														   																										   \
	constexpr bool Type<SomeType>::has_single_operator_binary_##OPERATOR() 				   																										   \
	{ 																					   																										   \
		return metaxxa::detail::___METAXXA___POSTCONDITION_OPERATOR_CHECKER_binary_##OPERATOR<SomeType, metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, void>::has()>::check(); \
	}

#define ___METAXXA___TYPE___DEFINE_NAMED_UNARY_AND_BINARY_OPERATOR(OPERATOR, UNARY_NAME, BINARY_NAME) \
	template <typename SomeType>													       																								       \
	template <typename Callable> 														   																								       \
	constexpr bool Type<SomeType>::has_operator_##UNARY_NAME() 							   																								       \
	{  																					   																								       \
		return metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, Callable>::has(); 																					       \
	} 																					   																								       \
	template <typename SomeType>													       																								       \
	constexpr bool Type<SomeType>::has_single_operator_##OPERATOR##_##UNARY_NAME()         																								       \
	{ 																					   																								       \
		return metaxxa::detail::___METAXXA___POSTCONDITION_OPERATOR_CHECKER_##UNARY_NAME<SomeType, metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, void>::has()>::check();  \
	} 																					   																								       \
	template <typename SomeType>														   																								       \
	template <typename Callable> 														   																								       \
	constexpr bool Type<SomeType>::has_operator_##BINARY_NAME() 						   																								       \
	{ 																					   																								       \
		return metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, Callable>::has(); 																				           \
	} 																					   																								       \
	template <typename SomeType>														   																								       \
	constexpr bool Type<SomeType>::has_single_operator_##OPERATOR##_##BINARY_NAME() 	   																								       \
	{ 																					   																								       \
		return metaxxa::detail::___METAXXA___POSTCONDITION_OPERATOR_CHECKER_##BINARY_NAME<SomeType, metaxxa::detail::___METAXXA___OPERATOR_TESTER_##OPERATOR<SomeType, void>::has()>::check(); \
	}

#endif // METAXXA_detail_TYPEHASOPERATORMETHODMACROS_H
