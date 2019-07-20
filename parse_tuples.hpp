#ifndef __PARSE_TUPLES_HPP__
#define __PARSE_TUPLES_HPP__

#include <algorithm>
#include <cstdint>
#include <string>
#include <map>

template<template<typename ...> typename TCollection, typename TUnit>
using IndexedTuples = std::map<uint64_t, std::map<uint64_t, TCollection<TUnit>>>;

template<template<typename ...> typename TCollection, typename TUnit>
using IndexedTuple = std::map<uint64_t, TCollection<TUnit>>;

/*!
 * \brief
 * It allows parsing of sequences of tuples.
 *
 * \param[in]  data				The input data.
 * \param[in]  tuples_sep		The sequence of symbols that separates tuples in the data.
 * \param[in] 	fields_sep		The sequence of symbols that separates fields in a tuple.
 * \param[out] tuples			The data structure that will be filled with parsed tuples.
 * \param[in]  offset			The number of tuples to skip from beginning.
 * \param[in]  size				The maximum number of tuples to retrieve. When 0 all tuples in content are retrieved.
 *
 * \return
 * It returns the reference to the tuple data structure given as input.
 */
template<template<typename...> typename TCollection, typename TUnit>
IndexedTuples<TCollection, TUnit>&  parse_tuples(
	const TCollection<TUnit> &data,
	const TCollection<TUnit> &tuples_sep,
	const TCollection<TUnit> &fields_sep,
	IndexedTuples<TCollection, TUnit> &tuples,
	uint64_t offset = 0,
	uint64_t size = 0){

	uint64_t i = 0;
	tuples.clear();

	if (data.empty())
		return tuples;

	auto i_prev = data.cbegin();
	auto i_content=data.cbegin();
	for (;i_content != data.cend(); i_prev = (i_content != data.cend()) ? ++i_content : data.cend(), ++i) {

		i_content = std::search(i_content,data.cend(),tuples_sep.begin(),tuples_sep.end());
		if (0 != offset && i < offset) continue;

		TCollection<TUnit> line(i_prev, i_content);
		IndexedTuple<TCollection, TUnit> fields;
		uint64_t j = 0;

		auto i_prev_l = line.cbegin();
		auto i_line = line.cbegin();
		for (;i_line != line.cend(); i_prev_l = (i_line != line.cend()) ? ++i_line : line.cend(), ++j) {
			i_line = std::search(i_line, line.cend(), fields_sep.begin(), fields_sep.end());
			fields.insert(std::make_pair(j, (fields_sep.size()!=0)?TCollection<TUnit>(i_prev_l, i_line):line));
		};

		tuples.insert(std::make_pair(i, fields));
		if (tuples.size() == size)break;
	}

	return tuples;
}

#endif