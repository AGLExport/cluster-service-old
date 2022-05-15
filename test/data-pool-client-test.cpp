/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service-test.c
 * @brief	Unit test fot data-pool-service-test.c
 */
#include <gtest/gtest.h>
#include "mock/syscall_io_mock.hpp"

// Test Terget files ---------------------------------------
extern "C" {
#include "../lib/data-pool-client.c"

int data_pool_set_v1(struct S_AGLCLUSTER_SERVICE_DATA_V1 *data)
{
		return 0;
}
}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct data_pool_client_test : Test, SyscallIOMockBase {};

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_client_test, data_pool_packet_check_v1__check)
{
	bool ret = -1;
	struct S_AGLCLUSTER_SERVICE_PACKETHEADER_V1 header;
	
	memset(&header,0,sizeof(header));
	
	//ff
	header.magic = 0;
	header.version = 0;

	ret = data_pool_packet_check_v1(&header);
	ASSERT_EQ(false, ret);

	//tf
	header.magic = AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC;
	header.version = 0;

	ret = data_pool_packet_check_v1(&header);
	ASSERT_EQ(false, ret);

	//ft
	header.magic = 0;
	header.version = AGLCLUSTER_SERVICE_PACKET_VERSION_V1;

	ret = data_pool_packet_check_v1(&header);
	ASSERT_EQ(false, ret);

	//tt
	header.magic = AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC;
	header.version = AGLCLUSTER_SERVICE_PACKET_VERSION_V1;

	ret = data_pool_packet_check_v1(&header);
	ASSERT_EQ(true, ret);
}


//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_client_test, data_pool_receive__read_error)
{
	int ret = -1;
	int dmyfd = 1234;
	
	EXPECT_CALL(sysiom, read(dmyfd, _, sizeof(AGLCLUSTER_SERVICE_PACKET)))
				.WillOnce(Return(-1));

	ret = data_pool_receive(dmyfd);
	ASSERT_EQ(-1, ret);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_client_test, data_pool_receive__read_size_error)
{
	int ret = -1;
	int dmyfd = 1234;
	
	EXPECT_CALL(sysiom, read(dmyfd, _, sizeof(AGLCLUSTER_SERVICE_PACKET)))
				.WillOnce(Return(1));

	ret = data_pool_receive(dmyfd);
	ASSERT_EQ(-1, ret);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_client_test, data_pool_receive__read_packeterror)
{
	int ret = -1;
	int dmyfd = 1234;
	
	EXPECT_CALL(sysiom, read(dmyfd, _, sizeof(AGLCLUSTER_SERVICE_PACKET)))
				.WillOnce(Return(sizeof(AGLCLUSTER_SERVICE_PACKET)));

	ret = data_pool_receive(dmyfd);
	ASSERT_EQ(-1, ret);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_client_test, data_pool_receive__read_success)
{
	int ret = -1;
	int dmyfd = 1234;
	
	EXPECT_CALL(sysiom, read(dmyfd, _, sizeof(AGLCLUSTER_SERVICE_PACKET)))
					.WillOnce(Invoke([](int fd, void *buf, size_t count) {
						AGLCLUSTER_SERVICE_PACKET *p = (AGLCLUSTER_SERVICE_PACKET*)buf;
						p->header.magic = AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC;
						p->header.version = AGLCLUSTER_SERVICE_PACKET_VERSION_V1;
						return sizeof(AGLCLUSTER_SERVICE_PACKET);
					}));

	ret = data_pool_receive(dmyfd);
	ASSERT_EQ(0, ret);

}
