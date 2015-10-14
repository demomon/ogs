/**
 * \file
 * \author Lars Bilke
 * \date   2010-02-09
 * \brief  Definition of the GEOModels class.
 *
 * \copyright
 * Copyright (c) 2012-2015, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef GEOMODELS_H
#define GEOMODELS_H

#include <QObject>

#include "GeoLib/GEOObjects.h"
#include "GeoLib/GeoType.h"

class GeoTreeModel;
class Model;
class PntsModel;
class StationTreeModel;
class PolylinesModel;
class SurfaceModel;
class TreeModel;

/**
 * \brief GEOModels connects the data management class GEOObjects and the GUI.
 * It inherits from GeoLib::GEOObjects and additionally emits signals when
 * data objects are modified. The GUI connects to these signals. Model instances
 * are created for every data object.
 */
class GEOModels : public QObject
{
	Q_OBJECT

public:
	GEOModels(QObject* parent = 0);
	~GEOModels();

	void setGEOObjects(GeoLib::GEOObjects* geo_objects)
	{
		_geo_objects = geo_objects;

		_geo_objects->addPointVecCallback = [this](std::string const& name)
		{
			this->addPointVec(name);
		};

		_geo_objects->removePointVecCallback = [this](std::string const& name)
		{
			this->removePointVec(name);
		};

		_geo_objects->addStationVecCallback = [this](
		    std::vector<GeoLib::Point*>* stations, std::string const& name)
		{
			this->addStationVec(stations, name);
		};

		_geo_objects->removeStationVecCallback = [this](std::string const& name)
		{
			this->removeStationVec(name);
		};

		_geo_objects->addPolylineVecCallback = [this](std::string const& name)
		{
			this->addPolylineVec(name);
		};

		_geo_objects->appendPolylineVecCallback = [this](std::string const& name)
		{
			this->appendPolylineVec(name);
		};

		_geo_objects->removePolylineVecCallback = [this](std::string const& name)
		{
			this->removePolylineVec(name);
		};
	}

	GeoTreeModel* getGeoModel() { return _geoModel; }
	StationTreeModel* getStationModel() { return _stationModel; }

public slots:
	/**
	 * Updates the tree model if the underlying data in GEOObjects has changed.
	 * Technically it removes the geometry from the tree model (but not from GeoObjects)
	 * and re-adds the (modified) geometry.
	 */
	void updateGeometry(const std::string &geo_name);

	/// Removes all parts (points, lines, surfaces) of the geometry with the given name.
	virtual void removeGeometry(std::string geo_name, GeoLib::GEOTYPE type);

	void addPointVec(std::string const& name);

	void removePointVec(std::string const& name);

	void addStationVec(std::vector<GeoLib::Point*>* stations,
	                           std::string const& name);
	void removeStationVec(std::string const& name);

	void addPolylineVec(std::string const& name);

	void appendPolylineVec(std::string const& name);

	void removePolylineVec(std::string const& name);

	virtual void addSurfaceVec(std::vector<GeoLib::Surface*>* surfaces,
	                           const std::string &name,
	                           std::map<std::string,std::size_t>* sfc_names = NULL);

	/// @brief
	/// @param surfaces The surface vector.
	virtual bool appendSurfaceVec(const std::vector<GeoLib::Surface*> &surfaces,
	                              const std::string &name);
	virtual bool removeSurfaceVec(const std::string &name);

	/// Adds the name 'new_name' for the geo-object specified by the parameters
	void addNameForElement(const std::string &geometry_name, const GeoLib::GEOTYPE object_type, std::size_t id, std::string new_name);

	/// Adds a generic name to all points that are part of the specified geo-object
	void addNameForObjectPoints(const std::string &geometry_name, const GeoLib::GEOTYPE object_type, const std::string &geo_object_name, const std::string &new_name);

	/// Calls all necessary functions to connect polyline-segments and update all views and windows.
	void connectPolylineSegments(const std::string &geoName,
	                             std::vector<std::size_t> indexlist,
	                             double proximity,
	                             std::string ply_name,
	                             bool closePly,
	                             bool triangulatePly);

protected:
	GeoTreeModel* _geoModel;
	StationTreeModel* _stationModel;

private:
	GeoLib::GEOObjects* _geo_objects;

signals:
	void geoDataAdded(GeoTreeModel*, std::string, GeoLib::GEOTYPE);
	void geoDataRemoved(GeoTreeModel*, std::string, GeoLib::GEOTYPE);

	void stationVectorAdded(StationTreeModel* model, std::string name);
	void stationVectorRemoved(StationTreeModel* model, std::string name);
};

#endif // GEOMODELS_H
