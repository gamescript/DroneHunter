/* Drone Hunter
// Copyright (C) 2017 LucKey Productions (luckeyproductions.nl)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "sceneobject.h"

SceneObject::SceneObject(Context *context):
    LogicComponent(context),
    destructable_{false},
    randomizer_{Random()}
{
}

void SceneObject::OnNodeSet(Node *node)
{
    for (int i{0}; i < 3; ++i){
        sampleSources_.Push(SharedPtr<SoundSource>(node_->CreateComponent<SoundSource>()));
        sampleSources_[i]->SetGain(0.3f);
        sampleSources_[i]->SetSoundType(SOUND_EFFECT);
    }
}

void SceneObject::Set(Vector3 position)
{
    node_->SetPosition(position);
    node_->SetEnabledRecursive(true);
}

void SceneObject::Disable()
{
    node_->SetEnabledRecursive(false);
}

void SceneObject::PlaySample(Sound* sample, float gain)
{
    for (SoundSource* s : sampleSources_){
        if (!s->IsPlaying()){
            s->SetGain(gain);
            s->Play(sample);
            break;
        }
    }
}
