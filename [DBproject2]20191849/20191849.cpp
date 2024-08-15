#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "encanto1017";
const char* db = "new_schema";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	const char* query;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		// 연동 코드

		FILE* fp;
		fp = fopen("20191849_1.txt", "r");
		if (!fp) {
			printf("file does not exist!\n");
			return 1;
		}
		char temp[1000];
		while (!feof(fp)) {
			query = fgets(temp, sizeof(temp), fp);
			mysql_query(connection, query);
		}
		fclose(fp);

		while (1) {
			int num;
			printf("-------- SELECT QUERY TYPES --------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			printf("\nSelect query : ");
			scanf("%d", &num);

			if (num == 0) {
				printf("----- QUIT -----\n\n");
				break;
			}

			else if (num == 1) {
				int num1;
				printf("---- TYPE 1 ----\n");
				printf("** Find address of homes for sale in the district“Mapo”**\n");

				char query1[400] = "SELECT property_id 	FROM property_on_market WHERE address_district = 'Mapo'";
				int state1 = 0;
				state1 = mysql_query(connection, query1);
				if (state1 == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s\t", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				else
					printf("error");
				printf("\n");


				printf("\n----- Subtypes in TYPE 1 -----\n");
				printf("\t1. TYPE 1-1\n");
				printf("\nSelect query : ");
				scanf("%d", &num1);

				if (num1 == 1) {
					printf("\n----- TYPE 1-1 -----\n");
					printf("** Then find the costing between ￦	1, 000, 000, 000 and ￦1, 500, 000, 000. **\n");
					char query1[300] = "SELECT property_id FROM property_on_market WHERE address_district = 'Mapo' AND price BETWEEN 1000000000 AND 1500000000";
					int state1 = 0;
					state1 = mysql_query(connection, query1);
					if (state1 == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("%s\t", sql_row[0]);
						}
						mysql_free_result(sql_result);
					}
					printf("\n");
					continue;
				}
				break;
			}

			else if (num == 2) {
				int num2;
				printf("---- TYPE 2 ----\n");
				printf("** Find the address of homes for sale in the 8th school district. **\n");

				char query22[400]="SELECT property_id FROM property_on_market WHERE address_district IN ('Gangnam', 'Seocho')";
				int state22 = 0;
				state22 = mysql_query(connection, query22);
				if (state22 == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s\t", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				else
					printf("error");
				printf("\n");
				

                printf("\n----- Subtypes in TYPE 2 -----\n");
				printf("\t1. TYPE 2-1\n");
                printf("\nSelect query : ");					
				scanf("%d", &num2);

                if (num2 == 1) {
						printf("\n----- TYPE 2-1 -----\n");
						printf("** Then find properties with 4 or more bedrooms and 2 bathrooms. **\n");
						char query2[300] = "SELECT property_id  FROM property_on_market WHERE address_district IN('Gangnam', 'Seocho') AND num_bedroom >= 4 AND num_bathroom = 2";
						int state2 = 0;
						state2 = mysql_query(connection, query2);
						if (state2 == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\t", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
						printf("\n");
						continue;
					}								
					break;
			}

			else if (num == 3) {
				int num3;
				printf("---- TYPE 3 ----\n");
				printf("** Find the name of the agent who has sold the most properties in the year 2022 by total won value.**\n");

				char query3[500] = "SELECT agent_id.agent_name FROM agent_id JOIN property_sold ON agent_id.agent_id = property_sold.agent_id WHERE YEAR(property_sold.date_sold) = 2022 GROUP BY agent_id.agent_name ORDER BY SUM(property_sold.price) DESC LIMIT 1";


				int state3 = 0;
				state3 = mysql_query(connection, query3);
				if (state3 == 0) {
					sql_result = mysql_store_result(connection);
					if (sql_result != NULL) {
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("%s\t", sql_row[0]);
						}
					}
					else {
						printf("No data found.\n");
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
				}
				printf("\n");


				printf("\n----- Subtypes in TYPE 3 -----\n");
				printf("\t1. TYPE 3-1\n");
				printf("\t2. TYPE 3-2\n");
				printf("\nSelect query : ");
				scanf("%d", &num3);

				if (num3 == 1) {
					printf("\n----- TYPE 3-1 -----\n");
					printf("**  Find the top k agents in the year 2023 by total won value. **\n");
					
					int k;
					printf("Enter the value of k: ");
					scanf("%d", &k);

					char query31[500];
					//sprintf(query31, "SELECT agent_id.agent_name, SUM(property_sold.price) as total_value FROM agent_id JOIN property_sold ON agent_id.agent_id = property_sold.agent_id WHERE YEAR(property_sold.date_sold) = 2023 GROUP BY agent_id.agent_id ORDER BY total_value DESC LIMIT %d", k);
					sprintf(query31, "SELECT agent_id.agent_name, SUM(property_sold.price) AS total_value FROM agent_id JOIN property_sold ON agent_id.agent_id = property_sold.agent_id WHERE YEAR(property_sold.date_sold) = 2023 GROUP BY agent_id.agent_name ORDER BY total_value DESC LIMIT %d", k);

					//printf("Generated Query: %s\n", query31);

					int state31 = 0;
					state31 = mysql_query(connection, query31);
					if (state31 == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("%s\t%s\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
					}
					printf("\n");
					continue;
				}
				else if (num3 == 2) {
					printf("\n----- TYPE 3-2 -----\n");
					printf("**  Find the bottom 10%% agents in the year 2021 by total won value. **\n");

					// 먼저 하위 10% 에이전트 수를 계산합니다.
					char count_query[200] = "SELECT FLOOR(COUNT(DISTINCT agent_id) * 0.1) FROM property_sold WHERE YEAR(date_sold) = 2021";
					int limit_value = 0;
					int state_count = mysql_query(connection, count_query);
					if (state_count == 0) {
						sql_result = mysql_store_result(connection);
						if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							limit_value = atoi(sql_row[0]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
						continue;
					}

					// 하위 10% 에이전트를 찾는 최종 쿼리
					char query3_2[500];
					sprintf(query3_2, "SELECT agent_id.agent_name, SUM(property_sold.price) AS total_value FROM agent_id JOIN property_sold ON agent_id.agent_id = property_sold.agent_id WHERE YEAR(property_sold.date_sold) = 2021 GROUP BY agent_id.agent_name ORDER BY total_value ASC LIMIT %d", limit_value);

					int state32 = mysql_query(connection, query3_2);
					if (state32 == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("%s\t%s\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
					}
					printf("\n");
					continue;
				}

				break;
			}

			else if (num == 4) {
				printf("---- TYPE 4 ----\n");
				printf("** For each agent, compute the average selling price of properties sold in 2022, and the average time the property was on the market. **\n");

				char query4[500] = "SELECT agent_id.agent_name, AVG(property_sold.price) AS avg_selling_price, AVG(DATEDIFF(property_sold.date_sold, property_sold.date_upload)) AS avg_days_on_market FROM property_sold JOIN agent_id ON property_sold.agent_id = agent_id.agent_id WHERE YEAR(property_sold.date_sold) = 2022 GROUP BY agent_id.agent_name";

				int state4 = mysql_query(connection, query4);
				if (state4 == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("Agent Name: %s, Average Selling Price: %s, Average Days on Market: %s\n",
							sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
				}
				printf("\n");

				printf("\n----- Subtypes in TYPE 4 -----\n");
				printf("\t1. TYPE 4-1\n");
				printf("\t2. TYPE 4-2\n");
				printf("\nSelect query : ");
				int num4;
				scanf("%d", &num4);

				if (num4 == 1) {
					printf("\n----- TYPE 4-1 -----\n");
					printf("** Compute the maximum selling price of properties sold in 2023 for each agent. **\n");

					char query4_1[500] = "SELECT agent_id.agent_name, MAX(property_sold.price) AS max_selling_price FROM property_sold JOIN agent_id ON property_sold.agent_id = agent_id.agent_id WHERE YEAR(property_sold.date_sold) = 2023 GROUP BY agent_id.agent_name";


					int state4_1 = mysql_query(connection, query4_1);
					if (state4_1 == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("Agent Name: %s, Maximum Selling Price: %s\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
					}
					printf("\n");
					continue;
				}
				else if (num4 == 2) {
					printf("\n----- TYPE 4-2 -----\n");
					printf("** Compute the longest time the property was on the market for each agent. **\n");

					char query4_2[500] = "SELECT agent_id.agent_name, MAX(DATEDIFF(property_sold.date_sold, property_sold.date_upload)) AS longest_days_on_market FROM property_sold JOIN agent_id ON property_sold.agent_id = agent_id.agent_id GROUP BY agent_id.agent_name";


					int state4_2 = mysql_query(connection, query4_2);
					if (state4_2 == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("Agent Name: %s, Longest Time on Market: %s days\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
					}
					printf("\n");
					continue;
				}
			}



			else if (num == 5) {
				printf("---- TYPE 5 ----\n");
				printf("** Show photos of the most expensive studio, one-bedroom, multi-bedroom apartment(s), and detached house(s). **\n");

				// 가장 비싼 스튜디오, 원베드룸, 멀티베드룸 아파트, 단독 주택의 사진을 가져오는 쿼리
				char query5[1500] = "SELECT image.image_URL, property_on_market.property_type FROM property_on_market JOIN property_image_map ON property_on_market.property_id = property_image_map.property_id JOIN image ON property_image_map.image_id = image.image_type WHERE (property_on_market.property_type = 'studio' AND property_on_market.price = (SELECT MAX(price) FROM property_on_market WHERE property_type = 'studio')) OR (property_on_market.property_type = 'one bedroom apartment' AND property_on_market.price = (SELECT MAX(price) FROM property_on_market WHERE property_type = 'one bedroom apartment')) OR (property_on_market.property_type = 'multi bedroom apartment' AND property_on_market.price = (SELECT MAX(price) FROM property_on_market WHERE property_type = 'multi bedroom apartment')) OR (property_on_market.property_type = 'detached house' AND property_on_market.price = (SELECT MAX(price) FROM property_on_market WHERE property_type = 'detached house'))";

				int state5 = mysql_query(connection, query5);
				if (state5 == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s %s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
				}
				printf("\n");
				continue;
			}

			else if (num == 6) {
				printf("----- TYPE 6 -----\n");
				printf("** Record the sale of a property that had been listed as being available. **\n");

				// 판매된 매물의 정보를 가져오는 쿼리
				char query6[400] = "SELECT property_sold.property_id, property_sold.address_district, property_sold.price, property_sold.property_type, property_sold.num_bedroom, property_sold.num_bathroom, property_sold.date_sold, property_sold.buyer_id, agent_id.agent_name "
					"FROM property_sold "
					"JOIN agent_id ON property_sold.agent_id = agent_id.agent_id "
					"ORDER BY property_sold.date_sold DESC";

				int state6 = mysql_query(connection, query6);
				if (state6 == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("Property ID: %s, District: %s, Price: %s, Type: %s, Bedrooms: %s, Bathrooms: %s, Sold Date: %s, Buyer ID: %s, Agent Name: %s\n",
							sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6], sql_row[7], sql_row[8]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
				}
				printf("\n");
				continue;
}


			else if (num == 7) {
				printf("----- TYPE 7 -----\n");
				printf("** Add a new agent to the database. **\n");

				// 사용자로부터 agent_id와 agent_name을 입력받음
				char agent_id[10];
				char agent_name[50];

				printf("Enter new agent ID: ");
				scanf("%s", agent_id);

				printf("Enter new agent name: ");
				scanf("%s", agent_name);

				// 새로운 에이전트를 추가하는 쿼리
				char query7[400];
				sprintf(query7, "INSERT INTO agent_id (agent_id, agent_name) VALUES ('%s', '%s')", agent_id, agent_name);

				int state7 = mysql_query(connection, query7);
				if (state7 == 0) {
					printf("New agent added successfully.\n");

					// 에이전트 리스트를 확인하기 위해 추가된 에이전트를 출력하는 쿼리
					char select_query[200];
					sprintf(select_query, "SELECT * FROM agent_id WHERE agent_id = '%s'", agent_id);
					state7 = mysql_query(connection, select_query);
					if (state7 == 0) {
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("Agent ID: %s, Agent Name: %s\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
					}
				}
				else {
					printf("Query Error %d: %s\n", mysql_errno(connection), mysql_error(connection));
				}
				printf("\n");
				continue;
				}

			else break;
		}
	}
	FILE* fp2 = NULL;
	fp2 = fopen("20191849_2.txt", "r");
	if (!fp2) {
		printf("file does not exist!\n");
		return 1;
	}
	char temp2[1000];
	while (!feof(fp2)) {
		query = fgets(temp2, sizeof(temp2), fp2);
		mysql_query(connection, query);
	}
	fclose(fp2);

	return 0;
}