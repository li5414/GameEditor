﻿#include "SQLiteTable.h"
#include "SQLite.h"
#include "Utility.h"

SQLiteTable::SQLiteTable(const std::string& name, SQLite* sqlite)
{
	mTableName = name;
	mSQLite = sqlite;
}
int SQLiteTable::getCol(const std::string& colName)
{
	int count = COL_NAME.size();
	for (int i = 0; i < count; ++i)
	{
		if (COL_NAME[i] == colName)
		{
			return i;
		}
	}
	return -1;
}
void SQLiteTable::registeColumn(const std::string& colName)
{
	COL_NAME.push_back(colName);
}
bool SQLiteTable::doUpdate(const std::string& updateString, const std::string& conditionString)
{
	std::string queryStr = "UPDATE " + mTableName + " SET " + updateString + " WHERE " + conditionString;
	return mSQLite->executeNonQuery(queryStr);
}
bool SQLiteTable::doInsert(const std::string& valueString)
{
	std::string queryString = "INSERT INTO " + mTableName + " VALUES (" + valueString + ")";
	return mSQLite->executeNonQuery(queryString);
}
void SQLiteTable::appendValueString(std::string& queryStr, const std::string& str, bool isEnd)
{
	queryStr += "\"" + str + "\"";
	if (!isEnd)
	{
		queryStr += ",";
	}
}
void SQLiteTable::appendValueInt(std::string& queryStr, int value, bool isEnd)
{
	queryStr += StringUtility::intToString(value);
	if (!isEnd)
	{
		queryStr += ",";
	}
}
void SQLiteTable::appendValueFloatArray(std::string& queryStr, const txVector<float>& floatArray, bool isEnd)
{
	appendValueString(queryStr, StringUtility::floatArrayToString(floatArray), isEnd);
}
void SQLiteTable::appendConditionString(std::string& condition, const std::string& col, const std::string& str, const std::string& operate)
{
	condition += col + " = " + "\"" + str + "\"" + operate;
}
void SQLiteTable::appendConditionInt(std::string& condition, const std::string& col, int value, const std::string& operate)
{
	condition += col + " = " + StringUtility::intToString(value) + operate;
}
void SQLiteTable::appendUpdateString(std::string& updateInfo, const std::string& col, const std::string& str, bool isEnd)
{
	updateInfo += col + " = " + "\"" + str + "\"";
	if (!isEnd)
	{
		updateInfo += ",";
	}
}
void SQLiteTable::appendUpdateInt(std::string& updateInfo, const std::string& col, int value, bool isEnd)
{
	updateInfo += col + " = " + StringUtility::intToString(value);
	if (!isEnd)
	{
		updateInfo += ",";
	}
}
void SQLiteTable::appendUpdateFloatArray(std::string& updateInfo, const std::string& col, const txVector<float>& floatArray, bool isEnd)
{
	appendUpdateString(updateInfo, col, StringUtility::floatArrayToString(floatArray), isEnd);
}