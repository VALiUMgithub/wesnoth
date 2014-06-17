/*
   Copyright (C) 2014 by Chris Beck <render787@gmail.com>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

// This class encapsulates the animation functionality of unit.

#ifndef UNIT_ANIM_COMP_HPP
#define UNIT_ANIM_COMP_HPP

#include "halo.hpp"
#include "unit_animation.hpp" //Note: only needed for enum

#include <boost/scoped_ptr.hpp>

class unit;

class unit_animation_component
{
public:
	/** States for animation. */
	enum STATE {
		STATE_STANDING,   /** anim must fit in a hex */
		STATE_FORGET,     /** animation will be automatically replaced by a standing anim when finished */
		STATE_ANIM};      /** normal anims */

	unit_animation_component(unit & my_unit) : 
		u_(my_unit),
		anim_(NULL),
		state_(STATE_STANDING), 
		next_idling_(0),
		frame_begin_time_(0),
		draw_bars_(false), 
		refreshing_(false),
		unit_halo_(halo::NO_HALO) {}

	unit_animation_component(unit & my_unit, const unit_animation_component & o) : 
		u_(my_unit),
		anim_(NULL),
		state_(o.state_),
		next_idling_(0),
		frame_begin_time_(o.frame_begin_time_),
		draw_bars_(o.draw_bars_),
		refreshing_(o.refreshing_),
		unit_halo_(halo::NO_HALO) {}

	const unit_animation* choose_animation(const display& disp,
		       	const map_location& loc, const std::string& event,
		       	const map_location& second_loc = map_location::null_location(),
			const int damage=0,
			const unit_animation::hit_type hit_type = unit_animation::INVALID,
			const attack_type* attack=NULL,const attack_type* second_attack = NULL,
			int swing_num =0);

	void set_standing(bool with_bars = true);

	void set_ghosted(bool with_bars = true);
	void set_disabled_ghosted(bool with_bars = true);

	void set_idling();
	void set_selecting();

	void start_animation (int start_time, const unit_animation *animation,
		bool with_bars,  const std::string &text = "",
		Uint32 text_color = 0, STATE state = STATE_ANIM);

	bool invalidate(const display & disp);

	void refresh();

	void clear_haloes();

	void reset_after_advance();

	unit_animation* get_animation() const { return anim_.get(); }

	friend class unit;
	friend class drawable_unit;
private:
	const unit & u_;

	boost::scoped_ptr<unit_animation> anim_;

	STATE state_; //animation state

	int next_idling_;      // used for animation
	int frame_begin_time_; // used for animation

	bool draw_bars_;
	bool refreshing_; // avoid infinite recursion. flag used for drawing / animation

	int unit_halo_; // flag used for drawing / animation
};

#endif
