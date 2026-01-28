#ifndef ApplicationPaths_h__
#define ApplicationPaths_h__

const char* const OCC_SPECTRUM  = "temp/occ_spectrum.bmp";
const char* const HIST_IMAGE    = "temp/hist.bmp";
const char* const VOL_IMAGE     = "temp/vol.dds";
const char* const VOL_META_FILE = "temp/vol.dat";
const char* const WORK_IMAGE    = "temp/out.dds";
const char* const DEPTH_IMAGE   = "temp/depth.bmp";
const char* const VIS_MAPPING   = "temp/vis.cfg";

const char* const INITIAL_COLOR_TABLE           = "data/images/Magic.tga";
const char* const INITIAL_COLOR_TABLE_PREVIEW   = "Magic_preview.bmp";
const char* const OPACITY_TEXTURE               = "data/images/opacity.tga";
const char* const PATH_COLOR_TABLES             = "data/images/";

const char* const FRAGMENT_SHADER_VOL   = "data/shader/volume.frag";
const char* const VERTEX_SHADER_VOL     = "data/shader/volume.vert";
const char* const FRAGMENT_SHADER_SLICE = "data/shader/seisline.frag";
const char* const VERTEX_SHADER_SLICE   = "data/shader/seisline.vert";


#endif // ApplicationPaths_h__