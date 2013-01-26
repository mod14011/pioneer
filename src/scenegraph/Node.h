// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _NODE_H
#define _NODE_H
/*
 * Generic node for the model scenegraph
 */
#include "libs.h"
#include "RefCounted.h"
#include "LmrTypes.h" //for renderdata

namespace Graphics { class Renderer; }

namespace SceneGraph
{

class NodeVisitor;

enum NodeMask {
	NODE_SOLID = 0x1,
	NODE_TRANSPARENT = 0x2,
	MASK_IGNORE = 0x4
};

class Node : public RefCounted
{
public:
	Node(Graphics::Renderer *r);
	Node(Graphics::Renderer *r, unsigned int nodemask);
	Node(const Node&);
	virtual const char *GetTypeName() { return "Node"; }
	virtual void Accept(NodeVisitor &v);
	virtual void Traverse(NodeVisitor &v);
	virtual void Render(const matrix4x4f &trans, RenderData *rd) { }
	void DrawAxes();
	void SetName(const std::string &name) { m_name = name; }
	const std::string &GetName() { return m_name; }

	virtual Node* FindNode(const std::string &);

	unsigned int GetNodeMask() const { return m_nodeMask; }
	void SetNodeMask(unsigned int m) { m_nodeMask = m; }

	Graphics::Renderer *GetRenderer() const { return m_renderer; }

protected:
	//can only to be deleted using DecRefCount
	virtual ~Node() { }
	std::string m_name;
	unsigned int m_nodeMask;
	Graphics::Renderer *m_renderer;
};

}

#endif
