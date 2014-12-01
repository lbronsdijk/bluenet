/**
 * Author: Bart van Vliet
 * Copyright: Distributed Organisms B.V. (DoBots)
 * Date: 6 Nov., 2014
 * License: LGPLv3+, Apache License, or MIT, your choice
 */
#ifndef __NRF_ADC__H__
#define __NRF_ADC__H__

#include <stdint.h>

#include <drivers/nrf_rtc.h>

#include <common/buffer.h>

#include <events/Dispatcher.h>

/**
 * Analog digital conversion class. 
 */
class ADC: public Dispatcher {
	private:
		ADC(): _buffer_size(100) {}
		ADC(ADC const&); // singleton, deny implementation
		void operator=(ADC const &); // singleton, deny implementation
	public:
		// use static variant of singelton, no dynamic memory allocation
		static ADC& getInstance() {
			static ADC instance;
			return instance;
		}

		// TODO: remove nrf_adc prefix. This is now C++.
		uint32_t nrf_adc_init(uint8_t pin);
		uint32_t nrf_adc_config(uint8_t pin);
		void nrf_adc_start();
		void nrf_adc_stop();

		// function to be called from interrupt, do not do much there!
		void update(uint32_t value);

		// in the program loop, time to dispatch events e.g.
		void tick();

		buffer_t<uint16_t>* getBuffer();

	protected:

	private:
		int _buffer_size;
};


#endif
