/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#include <kithare/ast.hpp>


kh::Ast::Ast(const std::vector<std::shared_ptr<kh::AstImport>>& _imports,
             const std::vector<std::shared_ptr<kh::AstFunctionExpression>>& _functions,
             const std::vector<std::shared_ptr<kh::AstUserType>>& _user_types,
             const std::vector<std::shared_ptr<kh::AstEnumType>>& _enums,
             const std::vector<std::shared_ptr<kh::AstDeclarationExpression>>& _variables)
    : variables(_variables), imports(_imports), functions(_functions), user_types(_user_types),
      enums(_enums) {}

kh::AstImport::AstImport(const size_t _index, const std::vector<std::u32string>& _path,
                         const bool _is_include, const bool _is_relative,
                         const std::u32string& _identifier)
    : index(_index), path(_path), is_include(_is_include), is_relative(_is_relative),
      identifier(_identifier) {}

kh::AstUserType::AstUserType(const size_t _index, const std::vector<std::u32string>& _identifiers,
                             const std::vector<std::shared_ptr<kh::AstIdentifierExpression>>& _bases,
                             const std::vector<std::u32string>& _generic_args,
                             const std::vector<std::shared_ptr<kh::AstDeclarationExpression>>& _members,
                             const std::vector<std::shared_ptr<kh::AstFunctionExpression>>& _methods,
                             const bool _is_class)
    : index(_index), identifiers(_identifiers), bases(_bases), generic_args(_generic_args),
      members(_members), methods(_methods), is_class(_is_class) {}

kh::AstEnumType::AstEnumType(const size_t _index, const std::vector<std::u32string>& _identifiers,
                             const std::vector<std::u32string>& _members,
                             const std::vector<uint64_t>& _values)
    : index(_index), identifiers(_identifiers), members(_members), values(_values) {}

kh::AstIdentifierExpression::AstIdentifierExpression(
    const size_t _index, const std::vector<std::u32string>& _identifiers,
    const std::vector<std::shared_ptr<kh::AstIdentifierExpression>>& _generics,
    const std::vector<size_t>& _generics_refs,
    const std::vector<std::vector<uint64_t>>& _generics_array)
    : identifiers(_identifiers), generics(_generics), generics_refs(_generics_refs),
      generics_array(_generics_array) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::IDENTIFIER;
}

kh::AstUnaryExpression::AstUnaryExpression(const size_t _index, const kh::Operator _operation,
                                           std::shared_ptr<kh::AstExpression>& _rvalue)
    : operation(_operation), rvalue(_rvalue) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::UNARY;
}

kh::AstRevUnaryExpression::AstRevUnaryExpression(const size_t _index, const kh::Operator _operation,
                                           std::shared_ptr<kh::AstExpression>& _rvalue)
    : operation(_operation), rvalue(_rvalue) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::REV_UNARY;
}

kh::AstBinaryExpression::AstBinaryExpression(const size_t _index, const kh::Operator _operation,
                                             std::shared_ptr<kh::AstExpression>& _lvalue,
                                             std::shared_ptr<kh::AstExpression>& _rvalue)
    : operation(_operation), lvalue(_lvalue), rvalue(_rvalue) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::BINARY;
}

kh::AstTernaryExpression::AstTernaryExpression(const size_t _index,
                                               std::shared_ptr<kh::AstExpression>& _condition,
                                               std::shared_ptr<kh::AstExpression>& _value,
                                               std::shared_ptr<kh::AstExpression>& _otherwise)
    : condition(_condition), value(_value), otherwise(_otherwise) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::TERNARY;
}

kh::AstComparisonExpression::AstComparisonExpression(
    const size_t _index, const std::vector<kh::Operator>& _operations,
    const std::vector<std::shared_ptr<kh::AstExpression>>& _values)
    : operations(_operations), values(_values) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::COMPARISON;
}

kh::AstSubscriptExpression::AstSubscriptExpression(
    const size_t _index, std::shared_ptr<kh::AstExpression>& _expression,
    const std::vector<std::shared_ptr<kh::AstExpression>>& _arguments)
    : expression(_expression), arguments(_arguments) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::SUBSCRIPT;
}

kh::AstCallExpression::AstCallExpression(
    const size_t _index, std::shared_ptr<kh::AstExpression>& _expression,
    const std::vector<std::shared_ptr<kh::AstExpression>>& _arguments)
    : expression(_expression), arguments(_arguments) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::CALL;
}

kh::AstDeclarationExpression::AstDeclarationExpression(
    const size_t _index, std::shared_ptr<kh::AstIdentifierExpression>& _var_type,
    const std::vector<uint64_t>& _var_array, const std::u32string& _var_name,
    std::shared_ptr<kh::AstExpression>& _expression, const size_t _refs, const bool _is_static,
    const bool _is_public)
    : var_type(_var_type), var_array(_var_array), var_name(_var_name), expression(_expression),
      refs(_refs), is_static(_is_static), is_public(_is_public) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::DECLARE;
}

kh::AstFunctionExpression::AstFunctionExpression(
    const size_t _index, const std::vector<std::u32string>& _identifiers,
    const std::vector<std::u32string>& _generic_args, const std::vector<uint64_t>& _return_array,
    std::shared_ptr<kh::AstIdentifierExpression>& _return_type, const size_t _return_refs,
    const std::vector<std::shared_ptr<kh::AstDeclarationExpression>>& _arguments,
    const std::vector<std::shared_ptr<kh::AstBody>>& _body, const bool _is_conditional,
    const bool _is_static, const bool _is_public)
    : index(_index), identifiers(_identifiers), generic_args(_generic_args),
      return_array(_return_array), return_type(_return_type), return_refs(_return_refs),
      arguments(_arguments), body(_body), is_conditional(_is_conditional), is_static(_is_static),
      is_public(_is_public) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::FUNCTION;
}

kh::AstScopeExpression::AstScopeExpression(const size_t _index,
                                           std::shared_ptr<kh::AstExpression>& _expression,
                                           const std::vector<std::u32string>& _identifiers)
    : expression(_expression), identifiers(_identifiers) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::SCOPE;
}

kh::AstConstValue::AstConstValue(const size_t _index, const char32_t _character,
                                 const kh::AstConstValue::ValueType _value_type)
    : value_type((ValueType)((size_t)_value_type)) {
    this->index = _index;
    this->character = _character;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::CONSTANT;
}

kh::AstConstValue::AstConstValue(const size_t _index, const uint64_t _uinteger,
                                 const kh::AstConstValue::ValueType _value_type)
    : value_type((ValueType)((size_t)_value_type)) {
    this->index = _index;
    this->uinteger = _uinteger;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::CONSTANT;
}

kh::AstConstValue::AstConstValue(const size_t _index, const int64_t _integer,
                                 const kh::AstConstValue::ValueType _value_type)
    : value_type((ValueType)((size_t)_value_type)) {
    this->index = _index;
    this->integer = _integer;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::CONSTANT;
}

kh::AstConstValue::AstConstValue(const size_t _index, const double _floating,
                                 const kh::AstConstValue::ValueType _value_type)
    : value_type((ValueType)((size_t)_value_type)) {
    this->index = _index;
    this->floating = _floating;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::CONSTANT;
}

kh::AstConstValue::AstConstValue(const size_t _index, const std::string& _buffer,
                                 const kh::AstConstValue::ValueType _value_type)
    : value_type((ValueType)((size_t)_value_type)) {
    this->index = _index;
    this->buffer = _buffer;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::CONSTANT;
}

kh::AstConstValue::AstConstValue(const size_t _index, const std::u32string& _string,
                                 const kh::AstConstValue::ValueType _value_type)
    : value_type((ValueType)((size_t)_value_type)) {
    this->index = _index;
    this->string = _string;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::CONSTANT;
}

kh::AstTupleExpression::AstTupleExpression(
    const size_t _index, const std::vector<std::shared_ptr<kh::AstExpression>>& _elements)
    : elements(_elements) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::TUPLE;
}

kh::AstListExpression::AstListExpression(
    const size_t _index, const std::vector<std::shared_ptr<kh::AstExpression>>& _elements)
    : elements(_elements) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::LIST;
}

kh::AstDictExpression::AstDictExpression(const size_t _index,
                                         const std::vector<std::shared_ptr<kh::AstExpression>>& _keys,
                                         const std::vector<std::shared_ptr<kh::AstExpression>>& _items)
    : keys(_keys), items(_items) {
    this->index = _index;
    this->type = kh::AstBody::Type::EXPRESSION;
    this->expression_type = kh::AstExpression::ExType::DICT;
}

kh::AstIf::AstIf(const size_t _index,
                 const std::vector<std::shared_ptr<kh::AstExpression>>& _conditions,
                 const std::vector<std::vector<std::shared_ptr<kh::AstBody>>>& _bodies,
                 const std::vector<std::shared_ptr<kh::AstBody>>& _else_body)
    : conditions(_conditions), bodies(_bodies), else_body(_else_body) {
    this->index = _index;
    this->type = kh::AstBody::Type::IF;
}

kh::AstWhile::AstWhile(const size_t _index, std::shared_ptr<kh::AstExpression>& _condition,
                       const std::vector<std::shared_ptr<kh::AstBody>>& _body)
    : condition(_condition), body(_body) {
    this->index = _index;
    this->type = kh::AstBody::Type::WHILE;
}

kh::AstDoWhile::AstDoWhile(const size_t _index, std::shared_ptr<kh::AstExpression>& _condition,
                           const std::vector<std::shared_ptr<kh::AstBody>>& _body)
    : condition(_condition), body(_body) {
    this->index = _index;
    this->type = kh::AstBody::Type::DO_WHILE;
}

kh::AstFor::AstFor(const size_t _index, std::shared_ptr<kh::AstExpression>& _initialize,
                   std::shared_ptr<kh::AstExpression>& _condition,
                   std::shared_ptr<kh::AstExpression>& _step,
                   const std::vector<std::shared_ptr<kh::AstBody>>& _body)
    : initialize(_initialize), condition(_condition), step(_step), body(_body) {
    this->index = _index;
    this->type = kh::AstBody::Type::FOR;
}

kh::AstForEach::AstForEach(const size_t _index, std::shared_ptr<kh::AstExpression>& _target,
                           std::shared_ptr<kh::AstExpression>& _iterator,
                           const std::vector<std::shared_ptr<kh::AstBody>>& _body)
    : target(_target), iterator(_iterator), body(_body) {
    this->index = _index;
    this->type = kh::AstBody::Type::FOREACH;
}

kh::AstStatement::AstStatement(const size_t _index, const kh::AstStatement::Type _statement_type,
                               std::shared_ptr<kh::AstExpression>& _expression)
    : statement_type((Type)((size_t)_statement_type)), expression(_expression) {
    this->index = _index;
    this->type = kh::AstBody::Type::STATEMENT;
}

kh::AstStatement::AstStatement(const size_t _index, const kh::AstStatement::Type _statement_type,
                               const size_t _loop_count)
    : statement_type((Type)((size_t)_statement_type)), loop_count(_loop_count) {
    this->index = _index;
    this->type = kh::AstBody::Type::STATEMENT;
}
