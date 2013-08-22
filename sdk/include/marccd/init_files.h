/* v3.0-00  2.1 reflections format - older 2.0 format
	    is listed as EXPERIMENTAL */

#define PEAKS		FILES[0]
#define TROIDINF        FILES[1]
#define SPOTLIST	FILES[2]
#define REFLECTIONS	FILES[3]
#define EXPERIMENTAL  FILES[9]
#define XENINTS          FILES[4]

#define BEAMLOG          FILES[6]

static char *GENERIC_NAMES[MAXITEMS] = {"x", "y", "frame"};

static FILE_DESCRIPTIONS FILES[MAXFILES] =
{	
	{
	"PEAKS",
	'F',
	0,
        {"nbytes", "x", "y", "z", "value", "number", "num",
	"firstfr", "frmn", "partl"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12, sizeof(int)+16, sizeof(int)+20, sizeof(int)+24, sizeof(int)+28, sizeof(int)+32}, 
        {'i', 'l', 'l', 'l', 'l', 'l', 'l', 'l', 'l', 'l'},
	{sizeof(int)+0, sizeof(int)+4, sizeof(int)+8},
	{0, 1, 2, 3, 4, 5, 6, 7},
	{0}
	},

	{
	"TROIDINF",
	'F',
	0,
	{"nbytes", "x", "y", "z", "frame1", "nframes", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12, sizeof(int)+16, sizeof(int)+20, sizeof(int)+24, sizeof(int)+28, sizeof(int)+32, sizeof(int)+36, sizeof(int)+40, sizeof(int)+44, sizeof(int)+48, sizeof(int)+52, sizeof(int)+56, sizeof(int)+60, sizeof(int)+64, sizeof(int)+68, sizeof(int)+72, sizeof(int)+76, sizeof(int)+80, sizeof(int)+84, sizeof(int)+88, sizeof(int)+92}, 
	{'i', 'f', 'f', 'f', 'l', 'l', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f'},
        {sizeof(int), sizeof(int)+4, sizeof(int)+8 },
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0},
	{0},
	},

	{
	"SPOTLIST",
	'F',
	0,
        {"nbytes", "iframe", "x", "y", "z", "hklid", "rlpn",
	"gamma", "srtind"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12, sizeof(int)+16, sizeof(int)+20, sizeof(int)+24, sizeof(int)+28 },
        {'i', 'l', 'f', 'f', 'f', 'l', 'f', 'f', 'l'},
        {sizeof(int)+4, sizeof(int)+8, sizeof(int)+12},
	{0, 0, 1, 2, 3, 5, 0, 4, 0, 0, 0},
	{2, 2, 0, 2, 4, 10, 0, 6, 4}
	},

	{
	"REFLECTIONS",
	'F',
	0,
        {"nbytes", "hklid", "x", "y", "z", "nmspt", "nmbac",
	"smmspt", "varspt", "smmbac", "varbac", "intns", "sgma",
        "iovsg", "rrate", "fidlp", "maskno", "errx", "erry", "errz",
        "intflg", "ldum1", "ldum2", "ldum3", "resolu"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12, sizeof(int)+16, sizeof(int)+20, sizeof(int)+24, sizeof(int)+28, sizeof(int)+32, sizeof(int)+36, sizeof(int)+40, sizeof(int)+44, sizeof(int)+48, sizeof(int)+52, sizeof(int)+56, sizeof(int)+60, sizeof(int)+64, sizeof(int)+68, sizeof(int)+72, sizeof(int)+76, sizeof(int)+80, sizeof(int)+84, sizeof(int)+88, sizeof(int)+92}, 
        {'i', 'l', 'f', 'f', 'f', 'l', 'l', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'l', 'f', 'f', 'f', 'l', 'l', 'l', 'l', 'f'},
        {sizeof(int)+4, sizeof(int)+8, sizeof(int)+12},
	{0, 7, 1, 2, 3, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0 ,0 ,0, 6, 0, 0, 0, 0},
	{0}
	},

	{
	"XENINTS",
	'F',
	0,
        {"nbytes", "hklid", "x", "y", "z", "idcode", "maskno",
	"res", "int", "intsd", "totcnt", "sptcnt",
		"errx", "erry", "errz", "res2"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12, sizeof(int)+16, sizeof(int)+20, sizeof(int)+24, sizeof(int)+28, sizeof(int)+32, sizeof(int)+36, sizeof(int)+40, sizeof(int)+44, sizeof(int)+48, sizeof(int)+52, sizeof(int)+56},
        {'i', 'l', 'f', 'f', 'f', 'l', 'l', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f'},
        {sizeof(int)+4, sizeof(int)+8, sizeof(int)+12},
	{0, 0, 1, 2, 3, 0, 0, 4, 5, 6, 0, 0, 0, 0, 0, 7},
	{0}
	},

	{
	"BEAM",
	0,
	40,
	{"n", "sum", "sum_bk", "x", "y", "sx", "sy", "e_count", "f_late", "e_time"},
	{0, 4, 8, 12, 16, 20, 24, 28, 32, 36},
	{'l', 'l', 'f', 'f', 'f', 'f', 'f', 'l', 'f', 'l'},
	{12, 16, 0},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
	{0},
	},

	{
	"BEAMLOG",
	'F',
	56,
	{"nbytes", "x", "y", "z", "raw", "rate", "sum", "elapsed", "e_count", "late_count", "datetime", "mask", "xcen", "ycen"},
	{0, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50},
	{'i', 'f', 'f', 'f', 'f', 'f', 'f', 'l', 'l', 'l', 'l', 'l', 'f', 'f'},
	{2, 6, 10},
	{0, 1, 2, 3, 4, 6, 5, 0, 7, 8, 0, 0, 0, 0},
	{1, 10, 0, 10, 4},
	},

	{
	"FLATETEST",
	'F',
	40,
	{"nbytes", "x", "y", "z", "beam", "rate", "count", "cpm", "c_cpm", "f_late"},
	{0, 2, 6, 10, 14, 18, 22, 26, 30, 34},
	{'i', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f'},
	{2, 6, 10},
	{0, 0, 0, 1, 2, 7, 3, 4, 5, 6},
	{0},
	},

	{
	"SENSE",
	'F',
	20,
	{"nbytes", "nx", "ny", "sensc", "radius"},
	{0, 2, 6, 10, 14},
	{'i', 'l', 'l', 'f', 'f'},
	{2, 6, 0},
	{0, 1, 2, 3, 4},
	{0},
	},

	{
	"PARAMS",
	'F',
	0,
	{"nbytes", ""},
	{0, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58,
	 62, 66, 70, 74, 78, 82, 86, 90, 94, 98, 102, 106, 110, 114,
	 118, 122, 126, 130},
 	{'i', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
	 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
         'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f'},	
	{0},
	{0},
	{0},
	},

	{
	"SPLINE",
	'F',
	0,
	{""},
	{0},
	{0},
	{0},
	{0},
	{0},
	},

	{
	"CENTROIDS",
	'F',
	0,
        {"nbytes", "x", "y", "sum"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8},
        {'i', 'f', 'f', 'f'},
        {sizeof(int), sizeof(int)+4},
	{0, 1, 2, 3},
	{0}
	},

	{
	"INDEXED_2D",
	'F',
	0,
        {"nbytes", "x", "y", "h", "k"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12},
        {'i', 'f', 'f', 'i', 'i'},
        {sizeof(int), sizeof(int)+4},
	{0, 1, 2, 3, 4},
	{0}
	},

	{
	"INDEXED_3D",
	'F',
	0,
        {"nbytes", "x", "y", "z", "h", "k", "l"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12,sizeof(int)+16, sizeof(int)+20},
        {'i', 'f', 'f', 'f', 'i', 'i', 'i'},
        {sizeof(int), sizeof(int)+4, sizeof(int)+8},
	{0, 1, 2, 3, 4, 5, 6},
	{0}
	},

	{
	"TWO_FLOATS",
	'F',
	0,
        {"nbytes", "f1", "f2"},
        {0, sizeof(int), sizeof(int)+4},
        {'i', 'f', 'f'},
        {sizeof(int), sizeof(int)+4},
	{0, 1, 2},
	{0}
	},

	{
	"THREE_FLOATS",
	'F',
	0,
        {"nbytes", "f1", "f2", "f3"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8},
        {'i', 'f', 'f', 'f'},
        {sizeof(int), sizeof(int)+4, sizeof(int)+8},
	{0, 1, 2, 3},
	{0}
	},

	{
	"FOUR_FLOATS",
	'F',
	0,
        {"nbytes", "f1", "f2", "f3", "f4"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12},
        {'i', 'f', 'f', 'f', 'f'},
        {sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12},
	{0, 1, 2, 3, 4},
	{0}
	},

	{
	"REFLECTIONS_V20",
	'F',
	0,
        {"nbytes", "hklid", "x", "y", "z", "nspot", "nback",
	"rate", "sumspt", "sumback", "fidlp", "maskn",
		"errx", "erry", "errz"},
        {0, sizeof(int), sizeof(int)+4, sizeof(int)+8, sizeof(int)+12, sizeof(int)+16, sizeof(int)+20, sizeof(int)+24, sizeof(int)+28, sizeof(int)+32, sizeof(int)+36, sizeof(int)+40, sizeof(int)+44, sizeof(int)+48, sizeof(int)+52},
        {'i', 'l', 'f', 'f', 'f', 'l', 'l', 'f', 'f', 'f', 'f', 'l', 'f', 'f', 'f'},
        {sizeof(int)+4, sizeof(int)+8, sizeof(int)+12},
	{0, 0, 1, 2, 3, 6, 7, 0, 4, 5, 0, 8},
	{0}
	},
};
