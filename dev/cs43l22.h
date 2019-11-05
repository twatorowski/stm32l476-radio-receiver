/**
 * @file cs43l22.h
 * 
 * @date 2019-11-05
 * @author your name (you@domain.com)
 * 
 * @brief CS43L22 DAC Driver Module
 */

#ifndef DEV_CS43L22_H_
#define DEV_CS43L22_H_

/** @brief callback argument */
typedef struct {
	/**< error code */
	int error;
    /* possible results */
    union {
        /* identification register */
        int id;
    };
} cs43l22_cbarg_t;

/**
 * @brief Read the identification register
 * 
 * @param cb end of operation callback
 * 
 * @return cs43l22_cbarg_t * status for CB_SYNC calls
 */
cs43l22_cbarg_t * CS43L22_ReadID(cb_t cb);

/**
 * @brief Initialize the DAC IC
 * 
 * @param cb end of operation callback
 * 
 * @return cs43l22_cbarg_t * status for CB_SYNC calls
 */
cs43l22_cbarg_t * CS43L22_Initialize(cb_t cb);

/**
 * @brief Starts the playback
 * 
 * @param cb end of operation callback
 * 
 * @return cs43l22_cbarg_t * status for CB_SYNC calls
 */
cs43l22_cbarg_t * CS43L22_Play(cb_t cb);

/**
 * @brief Sets the playback volume
 * 
 * @param db volume in decibels
 * @param cb end of operation callback
 * 
 * @return cs43l22_cbarg_t * status for CB_SYNC calls
 */
cs43l22_cbarg_t * CS43L22_Volume(int db, cb_t cb);

#endif /* DEV_CS43L22_H_ */
