#ifndef OSGEARTH_FEATURES_OPTIMIZER_HINTS_H
#define OSGEARTH_FEATURES_OPTIMIZER_HINTS_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_Engine/VBF_SGUtil/Optimizer>

namespace osgEarth { namespace Features
{
    /**
     * 优化提示，告诉优化器（osgUtil::Optimizer）明确包括或排除某些优化选项。
     * Filters that do their own optimization may wish to instruct the general OSG
     * optimizer to include or exclude certain optimization techniques. The FilterContext
     * carries an OptimizerHints object that can be used for this purpose.
     */
    class OSGEARTHFEATURES_EXPORT OptimizerHints
    {
    public:
        OptimizerHints();
        OptimizerHints( const OptimizerHints& rhs );
        virtual ~OptimizerHints() { }

		// 添加优化器应该使用的选项
        void include( osgUtil::Optimizer::OptimizationOptions options );

		// 添加优化器不应该使用的选项
        void exclude( osgUtil::Optimizer::OptimizationOptions options );

        /**
         * Gets the mask of options that the optimzer should expressly include.
         */
        osgUtil::Optimizer::OptimizationOptions getIncludedOptions() const;

        /**
         * Gets the mask of options that the optimizer should expressly exclude.
         */
        osgUtil::Optimizer::OptimizationOptions getExcludedOptions() const;

    private:
        int included;
        int excluded;
    };

} }

#endif // OSGEARTH_FEATURES_OPTIMIZER_HINTS_H
