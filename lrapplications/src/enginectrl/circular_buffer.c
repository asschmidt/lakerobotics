#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "gen/Node_ECU_Front_CAN_STM32F103.h"

#include "circular_buffer.h"

static void advance_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	if(cbuf->full)
    {
        cbuf->tail = (cbuf->tail + 1) % cbuf->max;
    }

	cbuf->head = (cbuf->head + 1) % cbuf->max;

	// We mark full because we will advance tail on the next time around
	cbuf->full = (cbuf->head == cbuf->tail);
}

static void retreat_pointer(cbuf_handle_t cbuf)
{
	assert(cbuf);

	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
}

cbuf_handle_t circular_buf_init(cbuf_handle_t cbuf, CAN_FRAME* buffer, size_t size)
{
	assert(buffer && size);

	cbuf->buffer = buffer;
	cbuf->max = size;
	circular_buf_reset(cbuf);

	assert(circular_buf_empty(cbuf));

	return cbuf;
}

void circular_buf_free(cbuf_handle_t cbuf)
{
	assert(cbuf);
	free(cbuf);
}

void circular_buf_reset(cbuf_handle_t cbuf)
{
    assert(cbuf);

    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = false;
}

size_t circular_buf_size(cbuf_handle_t cbuf)
{
	assert(cbuf);

	size_t size = cbuf->max;

	if(!cbuf->full)
	{
		if(cbuf->head >= cbuf->tail)
		{
			size = (cbuf->head - cbuf->tail);
		}
		else
		{
			size = (cbuf->max + cbuf->head - cbuf->tail);
		}

	}

	return size;
}

size_t circular_buf_capacity(cbuf_handle_t cbuf)
{
	assert(cbuf);

	return cbuf->max;
}

void circular_buf_put(cbuf_handle_t cbuf, CAN_FRAME* data)
{
	assert(cbuf && cbuf->buffer);

    //cbuf->buffer[cbuf->head] = data;
    memcpy(&(cbuf->buffer[cbuf->head]), data, sizeof(CAN_FRAME));

    advance_pointer(cbuf);
}

int circular_buf_put2(cbuf_handle_t cbuf, CAN_FRAME* data)
{
    int r = -1;

    assert(cbuf && cbuf->buffer);

    if(!circular_buf_full(cbuf))
    {
        //cbuf->buffer[cbuf->head] = data;
        memcpy(&(cbuf->buffer[cbuf->head]), data, sizeof(CAN_FRAME));
        advance_pointer(cbuf);
        r = 0;
    }

    return r;
}

int circular_buf_get(cbuf_handle_t cbuf, CAN_FRAME * data)
{
    assert(cbuf && data && cbuf->buffer);

    int r = -1;

    if(!circular_buf_empty(cbuf))
    {
        //*data = cbuf->buffer[cbuf->tail];
        memcpy(data, &(cbuf->buffer[cbuf->tail]), sizeof(CAN_FRAME));
        retreat_pointer(cbuf);

        r = 0;
    }

    return r;
}

bool circular_buf_empty(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return (!cbuf->full && (cbuf->head == cbuf->tail));
}

bool circular_buf_full(cbuf_handle_t cbuf)
{
	assert(cbuf);

    return cbuf->full;
}
