﻿#include "SQLite.h"
#include "Utility.h"
#include "SQLiteEquip.h"
#include "SQLiteMonster.h"
#include "SQLiteEffect.h"
#include "SQLiteDataReader.h"
#include "SQLiteSceneMap.h"
#include "SQLiteNPC.h"
#include "SQLiteMonGen.h"
#include "SQLiteMonsterInfo.h"
#include "SQLiteMagic.h"
#include "SQLiteStdItem.h"
#include "SQLiteAnimationFrame.h"

#define NEW_TABLE(type) m##type = TRACE_NEW(type, m##type, this)
#define DELETE_TABLE(type) TRACE_DELETE(m##type)

SQLite::SQLite(const string& dbFileName)
{
	// 打开数据库链接
	int ret = sqlite3_open(dbFileName.c_str(), &mSQlite3);
	if (ret != SQLITE_OK)
	{
		string errorInfo = sqlite3_errmsg(mSQlite3);
		return;
	}
	NEW_TABLE(SQLiteEquip);
	NEW_TABLE(SQLiteMonster);
	NEW_TABLE(SQLiteEffect);
	NEW_TABLE(SQLiteSceneMap);
	NEW_TABLE(SQLiteNPC);
	NEW_TABLE(SQLiteMonGen);
	NEW_TABLE(SQLiteMonsterInfo);
	NEW_TABLE(SQLiteMagic);
	NEW_TABLE(SQLiteStdItem);
	NEW_TABLE(SQLiteAnimationFrame);
}
void SQLite::destroy()
{
	DELETE_TABLE(SQLiteEquip);
	DELETE_TABLE(SQLiteMonster);
	DELETE_TABLE(SQLiteEffect);
	DELETE_TABLE(SQLiteSceneMap);
	DELETE_TABLE(SQLiteNPC);
	DELETE_TABLE(SQLiteMonGen);
	DELETE_TABLE(SQLiteMonsterInfo);
	DELETE_TABLE(SQLiteMagic);
	DELETE_TABLE(SQLiteStdItem);
	DELETE_TABLE(SQLiteAnimationFrame);
	sqlite3_close(mSQlite3);
}
bool SQLite::executeNonQuery(const string& queryString)
{
	sqlite3_stmt* stmt = NULL;
	if (sqlite3_prepare_v2(mSQlite3, queryString.c_str(), -1, &stmt, NULL) != SQLITE_OK)
	{
		return false;
	}
	sqlite3_step(stmt);
	return (sqlite3_finalize(stmt) == SQLITE_OK) ? true : false;
}

SQLiteDataReader* SQLite::executeQuery(const string& queryString)
{
	sqlite3_stmt* stmt = NULL;
	if (sqlite3_prepare_v2(mSQlite3, queryString.c_str(), -1, &stmt, NULL) != SQLITE_OK)
	{
		return NULL;
	}
	SQLiteDataReader* reader = TRACE_NEW(SQLiteDataReader, reader, stmt);
	return reader;
}

void SQLite::releaseReader(SQLiteDataReader* reader)
{
	TRACE_DELETE(reader);
}