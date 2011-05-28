#ifndef __Geom_SpatialIndex_OctTree_HPP__
#define __Geom_SpatialIndex_OctTree_HPP__

#include <utility>
#include <list>

#include <geom/Vector3D.hpp>
#include <geom/BoundingBox3D.hpp>

namespace Geom {
  namespace SpatialIndex {

    template <class ContentType>
    class OctTree {
      public:

        enum NodeType {
          LEFT_DOWN_NEAR  = 0,
          LEFT_DOWN_FAR   = 1,
          LEFT_UP_NEAR    = 2,
          LEFT_UP_FAR     = 3,
          RIGHT_DOWN_NEAR = 4,
          RIGHT_DOWN_FAR  = 5,
          RIGHT_UP_NEAR   = 6,
          RIGHT_UP_FAR    = 7,
          ROOT
        };

        class OctTreeNode;
        class OctTreeBranchNode;
        class OctTreeLeafNode;

        class OctTreeNode {
          public:
            OctTreeBranchNode *parent;
            NodeType type;

            BoundingBox3D bbox;

            OctTreeNode(OctTreeBranchNode *parent, NodeType type, 
                         const &BoundingBox3D bbox) 
             : parent(parent), type(type), bbox(bbox) {}

            virtual void insert(ContentType *content, const Vector3D &position) = 0;
            virtual void clear() = 0;
        };

        class OctTreeBranchNode : public OctTreeNode {
          public:
            Vector3D split_point;
            OctTreeNode *childs[8];    
            
            OctTreeBranchNode(OctTreeNode *parent, NodeType type, 
                               const &BoundingBox3D bbox, 
                               const &Vector3D split_point) 
             : OctTreeNode(parent, type, bbox), split_point(split_point) {}

            virtual void insert(ContentType *content, const Vector3D &position) {
              int child_id = ((position.x < split_point.x) << 2) |
                             ((position.y < split_point.y) << 1) |
                              (position.z < split_point.z) ;

              childs[child_id]->insert(content, position);
            }

            virtual void clear() {
              for (int child_id = 0; child_id < 8; ++child_id) {
                childs[child_id]->clear();
              }
            }
        };

        class OctTreeLeafNode : public OctTreeNode {
          public:
            static const int SIZE_LIMIT = 16;

            typedef std::list< pair<ContentType *, Vector3D> > ContentListType;
            ContentListType content_list;

            OctTreeLeafNode(OctTreeNode *parent, NodeType type, 
                             const &BoundingBox3D bbox) 
             : OctTreeNode(parent, type, bbox) {}

            void split() {
              ContentListType content_list_copy = content_list;
              content_list = ContentListType();

              // newbie split point selection
              Vector3D split_point = 0.5*(bbox.min + bbox.max);

              OctTreeBranchNode *new_node = new OctTreeBranchNode(parent, type, bbox, split_point);

              parent->childs[type] = new_node;

              new_node->childs[0] = this;
              parent = new_node;

              for (int type = 1; type < 8; ++type) {
                new_node->childs[type] = new OctTreeLeafNode(
                  new_node, type, 
                  BoundingBox3D( 
                    Vector3D(
                      ((type & 4) ? split_point.x : bbox.min.x),
                      ((type & 2) ? split_point.y : bbox.min.y),
                      ((type & 1) ? split_point.z : bbox.min.z)
                    ),
                    Vector3D(
                      ((type & 4) ? bbox.max.x : split_point.x),
                      ((type & 2) ? bbox.max.y : split_point.y),
                      ((type & 1) ? bbox.max.z : split_point.z)
                    )
                  )
                );
              }

              bbox.max = split_point;
              
              for (ContentListType::iterator content = content_list_copy.begin();
                    content != content_list_copy.end(); ++content) {
                new_node->insert(content->first, content->second);
              }              
            }

            virtual void insert(ContentType *content, const Vector3D &position) {
              content_list.push_back(content);

              if (content_list.size() > SIZE_LIMIT) split();
            }

            virtual void clear() {
              content_list = ContentListType();
            }
        };

        
    };

  }
}

#endif /* __Geom_SpatialIndex_OctTree_HPP__ */

