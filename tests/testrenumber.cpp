// SPDX-License-Identifier: GPL-2.0
#include "testrenumber.h"
#include "core/dive.h"
#include "core/divelist.h"
#include "core/file.h"
#include <QTextStream>

void TestRenumber::setup()
{
	QCOMPARE(parse_file(SUBSURFACE_TEST_DATA "/dives/test47.xml", &dive_table, &trip_table), 0);
	process_loaded_dives();
}

void TestRenumber::testMerge()
{
	struct dive_table table = { 0 };
	struct trip_table trips = { 0 };
	QCOMPARE(parse_file(SUBSURFACE_TEST_DATA "/dives/test47b.xml", &table, &trip_table), 0);
	process_imported_dives(&table, &trips, false, false, true);
	QCOMPARE(dive_table.nr, 1);
	QCOMPARE(unsaved_changes(), 1);
	mark_divelist_changed(false);
}

void TestRenumber::testMergeAndAppend()
{
	struct dive_table table = { 0 };
	struct trip_table trips = { 0 };
	QCOMPARE(parse_file(SUBSURFACE_TEST_DATA "/dives/test47c.xml", &table, &trip_table), 0);
	process_imported_dives(&table, &trips, false, false, true);
	QCOMPARE(dive_table.nr, 2);
	QCOMPARE(unsaved_changes(), 1);
	struct dive *d = get_dive(1);
	QVERIFY(d != NULL);
	if (d)
		QCOMPARE(d->number, 2);
}

QTEST_GUILESS_MAIN(TestRenumber)
