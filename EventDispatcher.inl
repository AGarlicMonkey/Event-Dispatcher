template<typename RetType, typename... FuncArgs>
inline RetType EventDispatcher<RetType, FuncArgs...>::broadcast(FuncArgs... args){
	function(args...);
}

template<typename RetType, typename... FuncArgs>
inline int EventDispatcher<RetType, FuncArgs...>::bind(std::function<RetType(FuncArgs...)> function){
	this->function = function;
	return -1;
}

template<typename RetType, typename... FuncArgs>
template<typename T>
inline int EventDispatcher<RetType, FuncArgs...>::bind(T* context, RetType(T::*function)(FuncArgs...)){
	return bind(std::bind(function, context));
}

template<typename RetType, typename... FuncArgs>
inline bool EventDispatcher<RetType, FuncArgs...>::unbind(int ID){

	return false;
}