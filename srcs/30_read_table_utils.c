/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_read_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:14:07 by anurtiag          #+#    #+#             */
/*   Updated: 2024/04/09 15:37:57 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**custom_function4(char **lines)
{
	lines[81] = "25\t4\t0\t5\t-1";
	lines[82] = "25\t-1\t1\t101\t2";
	lines[83] = "25\t105\t-1\t30\t-1";
	lines[84] = "25\t106\t-1\t23\t-1";
	lines[85] = "25\t107\t-1\t11\t-1";
	lines[86] = "25\t109\t-1\t12\t-1";
	lines[87] = "26\t-1\t1\t104\t2";
	lines[88] = "27\t-1\t1\t100\t3";
	lines[89] = "28\t-1\t1\t105\t2";
	lines[90] = "29\t-1\t1\t105\t2";
	lines[91] = "30\t0\t0\t28\t-1";
	lines[92] = "30\t1\t0\t2\t-1";
	lines[93] = "30\t2\t0\t3\t-1";
	lines[94] = "30\t3\t0\t4\t-1";
	lines[95] = "30\t4\t0\t5\t-1";
	lines[96] = "30\t-1\t1\t101\t3";
	lines[97] = "30\t106\t-1\t29\t-1";
	lines[98] = "30\t107\t-1\t11\t-1";
	lines[99] = "30\t109\t-1\t12\t-1";
	lines[100] = NULL;
	return (lines);
}

char	**custom_function3(char **lines)
{
	lines[63] = "20\t107\t-1\t11\t-1";
	lines[64] = "20\t109\t-1\t12\t-1";
	lines[65] = "21\t-1\t1\t105\t1";
	lines[66] = "22\t0\t0\t28\t-1";
	lines[67] = "22\t1\t0\t2\t-1";
	lines[68] = "22\t2\t0\t3\t-1";
	lines[69] = "22\t3\t0\t4\t-1";
	lines[70] = "22\t4\t0\t5\t-1";
	lines[71] = "22\t-1\t1\t101\t2";
	lines[72] = "22\t106\t-1\t29\t-1";
	lines[73] = "22\t107\t-1\t11\t-1";
	lines[74] = "22\t109\t-1\t12\t-1";
	lines[75] = "23\t-1\t1\t105\t1";
	lines[76] = "24\t-1\t1\t103\t1";
	lines[77] = "25\t0\t0\t21\t-1";
	lines[78] = "25\t1\t0\t2\t-1";
	lines[79] = "25\t2\t0\t3\t-1";
	lines[80] = "25\t3\t0\t4\t-1";
	lines = custom_function4(lines);
	return (lines);
}

char	**custom_function2(char **lines)
{
	lines[40] = "9\t103\t-1\t25\t-1";
	lines[41] = "9\t106\t-1\t26\t-1";
	lines[42] = "9\t107\t-1\t11\t-1";
	lines[43] = "9\t109\t-1\t12\t-1";
	lines[44] = "10\t-1\t1\t104\t1";
	lines[45] = "11\t-1\t1\t106\t1";
	lines[46] = "12\t-1\t1\t106\t1";
	lines[47] = "13\t-1\t1\t108\t1";
	lines[48] = "14\t-1\t1\t107\t2";
	lines[49] = "15\t-1\t1\t107\t2";
	lines[50] = "16\t-1\t1\t110\t1";
	lines[51] = "17\t-1\t1\t109\t2";
	lines[52] = "18\t-1\t1\t107\t2";
	lines[53] = "19\t-1\t2\t-1\t-1";
	lines[54] = "20\t0\t0\t1\t-1";
	lines[55] = "20\t1\t0\t2\t-1";
	lines[56] = "20\t2\t0\t3\t-1";
	lines[57] = "20\t3\t0\t4\t-1";
	lines[58] = "20\t4\t0\t5\t-1";
	lines[59] = "20\t101\t-1\t27\t-1";
	lines[60] = "20\t102\t-1\t8\t-1";
	lines[61] = "20\t104\t-1\t9\t-1";
	lines[62] = "20\t106\t-1\t10\t-1";
	lines = custom_function3(lines);
	return (lines);
}

char	**custom_function1(char **lines)
{
	lines[17] = "4\t0\t0\t16\t-1";
	lines[18] = "4\t110\t-1\t17\t-1";
	lines[19] = "5\t0\t0\t13\t-1";
	lines[20] = "5\t108\t-1\t18\t-1";
	lines[21] = "6\t-2\t0\t19\t-1";
	lines[22] = "6\t5\t0\t20\t-1";
	lines[23] = "7\t-1\t1\t100\t1";
	lines[24] = "8\t0\t0\t21\t-1";
	lines[25] = "8\t1\t0\t2\t-1";
	lines[26] = "8\t2\t0\t3\t-1";
	lines[27] = "8\t3\t0\t4\t-1";
	lines[28] = "8\t4\t0\t5\t-1";
	lines[29] = "8\t-1\t1\t101\t1";
	lines[30] = "8\t105\t-1\t22\t-1";
	lines[31] = "8\t106\t-1\t23\t-1";
	lines[32] = "8\t107\t-1\t11\t-1";
	lines[33] = "8\t109\t-1\t12\t-1";
	lines[34] = "9\t0\t0\t24\t-1";
	lines[35] = "9\t1\t0\t2\t-1";
	lines[36] = "9\t2\t0\t3\t-1";
	lines[37] = "9\t3\t0\t4\t-1";
	lines[38] = "9\t4\t0\t5\t-1";
	lines[39] = "9\t-1\t1\t101\t1";
	lines = custom_function2(lines);
	return (lines);
}

char	**custom_function(void)
{
	char	**lines;

	lines = (char **)malloc(NUM_LINES * sizeof(char *));
	if (!lines)
		return (lines);
	lines[0] = "0\t0\t0\t1\t-1";
	lines[1] = "0\t1\t0\t2\t-1";
	lines[2] = "0\t2\t0\t3\t-1";
	lines[3] = "0\t3\t0\t4\t-1";
	lines[4] = "0\t4\t0\t5\t-1";
	lines[5] = "0\t100\t-1\t6\t-1";
	lines[6] = "0\t101\t-1\t7\t-1";
	lines[7] = "0\t102\t-1\t8\t-1";
	lines[8] = "0\t104\t-1\t9\t-1";
	lines[9] = "0\t106\t-1\t10\t-1";
	lines[10] = "0\t107\t-1\t11\t-1";
	lines[11] = "0\t109\t-1\t12\t-1";
	lines[12] = "1\t-1\t1\t102\t1";
	lines[13] = "2\t0\t0\t13\t-1";
	lines[14] = "2\t108\t-1\t14\t-1";
	lines[15] = "3\t0\t0\t13\t-1";
	lines[16] = "3\t108\t-1\t15\t-1";
	lines = custom_function1(lines);
	return (lines);
}
