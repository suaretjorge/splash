/*
 * Copyright (C) 2014 Emmanuel Durand
 *
 * This file is part of Splash.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * blobserver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with blobserver.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * @mesh_shmdata.h
 * The Mesh_Shmdata_Shmdata class
 */

#ifndef SPLASH_MESH_SHMDATA_H
#define SPLASH_MESH_SHMDATA_H

#include "config.h"

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <shmdata/any-data-reader.h>

#include "coretypes.h"
#include "mesh.h"

namespace Splash {

class Mesh_Shmdata : public Mesh
{
    public:
        /**
         * Constructor
         */
        Mesh_Shmdata();

        /**
         * Destructor
         */
        ~Mesh_Shmdata();

        /**
         * No copy constructor, only move
         */
        Mesh_Shmdata(const Mesh_Shmdata&) = delete;
        Mesh_Shmdata& operator=(const Mesh_Shmdata&) = delete;

        Mesh_Shmdata(Mesh_Shmdata&& g) noexcept
        {
            *this = std::move(g);
        }

        Mesh_Shmdata& operator=(Mesh_Shmdata&& g) noexcept
        {
            if (this != &g)
            {
                _filename = g._filename;
                _reader = g._reader;
            }
            return *this;
        }

        /**
         * Set the path to read from
         */
        bool read(const std::string& filename);

    protected:
        std::string _filename;
        shmdata_any_reader_t* _reader {nullptr};

        /**
         * Shmdata callback
         */
        static void onData(shmdata_any_reader_t* reader, void* shmbuf, void* data, int data_size, unsigned long long timestamp,
            const char* type_description, void* user_data);

        /**
         * Register new functors to modify attributes
         */
        void registerAttributes();
};

typedef std::shared_ptr<Mesh_Shmdata> Mesh_ShmdataPtr;

} // end of namespace

#endif // SPLASH_MESH_SHMDATA_H